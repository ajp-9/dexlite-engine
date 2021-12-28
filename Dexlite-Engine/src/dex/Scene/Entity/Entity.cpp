#include "Entity.hpp"

#include "../Component/BaseComponent.hpp"
#include "../Component/Camera/CameraComponent.hpp"
#include "../Component/TagComponent.hpp"
#include "../Component/ModelComponent.hpp"
#include "../Component/TransformComponent.hpp"

namespace dex
{
    Entity::Entity(Scene* scene, std::string tag, bool add_to_root)
        : m_Handle(scene->m_Registry.create()), m_Scene(scene)
    {
        addComponent<Parent>(entt::null);
        addComponent<ChildrenHandles>();

        addComponent<Component::Tag>(tag);
        addComponent<Component::Transform>(*this);

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

        m_Scene->m_Registry.destroy(m_Handle);
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

    void Entity::removeChild(Entity child, bool destroy_handle)
    {
        const auto& children_handles = getChildrenHandles();

        const auto& it = std::find(children_handles.begin(), children_handles.end(), child);

        if (it != children_handles.end())
        {
            getChildrenHandles().erase(it);

            if (destroy_handle)
                m_Scene->m_Registry.destroy(child);
        }
        else
            DEX_LOG_ERROR("<dex::Entity::removeChild>: Entity (ID: {}), is not in ChildrenHandles component of Entity (ID: {}).", child.m_Handle, m_Handle);
    }

    void Entity::updateChildrenTransform()
    {
        const auto& children_handles = getChildrenHandles();

        for (entt::entity child_handle : children_handles)
        {
            Entity child_entity = Entity(child_handle, m_Scene);

            if (child_entity.getComponent<Component::Transform>().m_FlagChanged)
            {
                child_entity.getComponent<Component::Transform>().update();

                if (child_entity.hasComponent<Component::Camera>())
                {
                    auto& camera = child_entity.getComponent<Component::Camera>();

                    if (camera.IsEnabled)
                    {
                        if (!camera.m_Entity.isValid())
                            camera.m_Entity = child_entity;

                        camera.updateViewMatrix();
                    }
                }
            }

            child_entity.updateChildrenTransform();
        }
    }
}
