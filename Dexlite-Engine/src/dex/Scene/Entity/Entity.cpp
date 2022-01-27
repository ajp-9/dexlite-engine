#include "Entity.hpp"

#include "../Component/BaseComponent.hpp"
#include "../Component/Camera/CameraComponent.hpp"
#include "../Component/TagComponent.hpp"
#include "../Component/RelationshipComponents.hpp"
#include "../Component/ModelComponent.hpp"
#include "../Component/Transform/TransformComponent.hpp"

namespace dex
{
    Entity::Entity(Scene* scene, std::string tag, bool add_to_root)
        : m_Handle(scene->m_Registry.create()), m_Scene(scene)
    {
        addComponent<Component::Parent>();
        addComponent<Component::ChildrenHandles>();

        addComponent<Component::Tag>(tag);
        addComponent<Component::Transform>();

        scene->m_Entities.push_back(*this);

        if (add_to_root)
            scene->m_Root->addChild(*this);
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
        auto& children_handles = getChildrenHandles();

        for (entt::entity child_handle : children_handles)
        {
            m_Scene->m_Registry.destroy(child_handle);
        }

        children_handles.clear();
    }

    void addChild(entt::entity child_handle)
    {
        //getChildrenHandles().push_back(child_handle);
        //m_Scene->m_Registry.get<Component::Parent>(child_handle).Handle = m_Handle;
    }

    void Entity::removeChild(Entity child, bool destroy_handle)
    {
        const auto& children_handles = getChildrenHandles();

        const auto& iter = std::find(children_handles.begin(), children_handles.end(), child);

        if (iter != children_handles.end())
        {
            getChildrenHandles().erase(iter);

            if (destroy_handle)
                m_Scene->m_Registry.destroy(child);
        }
        else
            DEX_LOG_ERROR("<dex::Entity::removeChild>: Entity (ID: {}), is not in ChildrenHandles component of Entity (ID: {}).", child.m_Handle, m_Handle);
    }

    std::vector<entt::entity>& Entity::getChildrenHandles() const
    {
        return getComponent<Component::ChildrenHandles>().Handles;
    }

    std::vector<Entity> Entity::getChildren() const
    {
        std::vector<Entity> return_children;
        auto children_handles = getComponent<Component::ChildrenHandles>().Handles;

        for (auto& child_handle : children_handles)
        {
            return_children.emplace_back(Entity(child_handle, m_Scene));
        }

        return return_children;
    }

    // recursive
    void Entity::updateChildrenTransform()
    {
        const auto& children_handles = getChildrenHandles();

        for (entt::entity child_handle : children_handles)
        {
            Entity child_entity = Entity(child_handle, m_Scene);

            if (child_entity.getComponent<Component::Transform>().m_FlagChanged)
            {
                child_entity.getComponent<Component::Transform>().update();

                for (auto func : SceneManager::m_Entity_UpdateComponentWithTransform_Functions)
                    func(child_entity);
            }
            
            child_entity.updateChildrenTransform();
        }
    }

    void Entity::setParent(Entity parent)
    {
        getComponent<Component::Parent>().Handle = parent.m_Handle;
    }

    void Entity::setParent(entt::entity parent)
    {
        getComponent<Component::Parent>().Handle = parent;
    }

    Entity Entity::getParent()
    {
        return Entity(getComponent<Component::Parent>().Handle, m_Scene);
    }
}
