#include "Entity.hpp"

namespace dex
{
    Entity::Entity(Scene* scene)
        : m_Handle(scene->m_Registry.create()), m_Scene(scene)
    {
        addComponent<ChildrenHandles>();

        addComponent<Component::Tag>();
        addComponent<Component::Transform>();

        scene->m_Entities.push_back(*this);
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

    Entity Entity::addNewChild()
    {
        Entity child = { m_Scene };
        addChild(child);

        return child;
    }

    void Entity::removeChild(Entity child, bool destroy_handle)
    {
        auto& children_handles = getChildrenHandles();

        auto& it = std::find(children_handles.begin(), children_handles.end(), child);

        if (it != children_handles.end())
        {
            children_handles.erase(it);

            if (destroy_handle)
                m_Scene->m_Registry.destroy(child);
        }
        else
            DEX_LOG_ERROR("<dex::Entity::removeChild>: Entity (ID: {}), is not in ChildrenHandles component of Entity (ID: {}).", child.m_Handle, m_Handle);
    }

    inline std::vector<entt::entity>& Entity::getChildrenHandles()
    {
        return getComponent<ChildrenHandles>();
    }

    bool Entity::operator==(const Entity& other)
    {
        return m_Handle == other.m_Handle && m_Scene == other.m_Scene;
    }
}
