#include "Entity.hpp"

#include "../../Physics/Physics.hpp"

#include "../SceneManager.hpp"

#include "../Component/BaseComponent.hpp"
#include "../Component/Camera/CameraComponent.hpp"
#include "../Component/TagComponent.hpp"
#include "../Component/RelationshipComponents.hpp"
#include "../Component/ModelComponent.hpp"
#include "../Components.hpp"
#include "../Component/Transform/TransformComponent.hpp"

namespace dex
{
    Entity::Entity(Scene* scene, std::string tag, bool add_to_root)
        : m_Handle(scene->m_Registry.create()), m_Scene(scene)
    {
        addComponent<Component::Parent>();
        addComponent<Component::Children>();

        addComponent<Component::Tag>(tag);
        addComponent<Component::Transform>();

        scene->m_Entities.push_back(*this);

        if (add_to_root)
            scene->Root->addChild(*this);
    }

    Entity::Entity(entt::entity handle, Scene* scene)
        : m_Handle(handle), m_Scene(scene)
    {}

    void Entity::destroy()
    {
        destroyChildren();

        m_Scene->destroyEntity(*this);
    }

    void Entity::destroyChildren()
    {
        // Taking a copy b/c messing with a vec while looping will make bugs.
        auto children = getChildren();

        for (auto& child : children)
        {
            child.destroy();
        }

        children.clear();
    }

    void Entity::addChild(Entity child)
    {
        Entity current_parent_test = getParent();
        while (current_parent_test.m_Handle != entt::null)
        {
            if (current_parent_test == child)
            {
                DEX_LOG_ERROR("<dex::Entity::addChild()>: Can't make an entity ({}) a child of one of its descendants ({}).",
                    child.getComponent<Component::Tag>().m_Tag,
                    getComponent<Component::Tag>().m_Tag);

                return;
            }

            current_parent_test = current_parent_test.getParent();
        }

        getChildren().push_back(child);
        
        if (child.getParent().m_Handle != entt::null)
        {
            child.getParent().removeChild(child);
        }

        child.setParent(Entity(m_Handle, m_Scene));
    }

    void Entity::removeChild(Entity child, bool destroy_handle)
    {
        const auto& children_handles = getChildren();
        const auto& iter = std::find(children_handles.begin(), children_handles.end(), child);

        if (iter != children_handles.end())
        {
            getChildren().erase(iter);

            if (destroy_handle)
                child.destroy();
        }
        else
        {
            DEX_LOG_WARN("<dex::Entity::removeChild>: Entity (ID: {}), is not in ChildrenHandles component of Entity (ID: {}).", child.m_Handle, m_Handle);
        }
    }

    /*std::vector<entt::entity>& Entity::getChildrenHandles() const
    {
        return getComponent<Component::ChildrenHandles>().Handles;
    }*/

    std::vector<Entity>& Entity::getChildren() const
    {
        return getComponent<Component::Children>().Entities;
    }

    // recursive
    void Entity::updateChildrenTransform()
    {
        const auto& children = getChildren();

        for (auto child : children)
        {
            if (child.getComponent<Component::Transform>().m_FlagChanged)
            {
                child.getComponent<Component::Transform>().update(getComponent<Component::Transform>());

                for (auto func : SceneManager::m_Entity_UpdateComponentWithTransform_Functions)
                    func(child);
            }
            
            child.updateChildrenTransform();
        }
    }

    void Entity::setParent(Entity parent)
    {
        getComponent<Component::Parent>().Entity = parent;
    }

    Entity& Entity::getParent()
    {
        return getComponent<Component::Parent>().Entity;
    }
}
