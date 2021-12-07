#pragma once

#include <iostream>

#include "../Component/TagComponent.hpp"
#include "../Component/ModelComponent.hpp"
#include "../Component/TransformComponent.hpp"
#include "../../Util/Logging.hpp"
#include "../Scene.hpp"
     
namespace dex
{
    typedef std::vector<entt::entity> ChildrenHandles;

    // Does not need to be a shared pointer, since its small contents (handle ID and ptr to registry) would remain constant between its instances.
    class Entity
    {
    private:
        // Creates a new entity.
        Entity(Scene* scene)
            : m_Handle(scene->m_Registry.create()), m_Scene(scene)
        {
            addComponent<Component::Tag>();
            addComponent<Component::Transform>();

            addComponent<ChildrenHandles>();
        }
    public:
        // Creates a new class from a pre-existing entity handle.
        Entity(entt::entity handle, Scene* scene)
            : m_Handle(handle), m_Scene(scene)
        {}

        // Destroys the handle in the registry. This class would remain intact and should be disgarded afterwards.
        void destroy()
        {
            destroyChildren();

            m_Scene->m_Registry.destroy(m_Handle);
        }

        // Destroys all its children in the registry. Their classes would remain intact and should be disgarded afterwards.
        void destroyChildren()
        {
            auto& children_handles = getChildrenHandles();

            for (entt::entity child_handle : children_handles)
            {
                m_Scene->m_Registry.destroy(child_handle);
            }

            children_handles.clear();
        }

        bool isEntityValid()
        {
            return m_Scene->m_Registry.valid(m_Handle);
        }

        void addChild(Entity child)
        {
            getChildrenHandles().push_back(child.m_Handle);
        }

        void addChild(entt::entity child_handle)
        {
            getChildrenHandles().push_back(child_handle);
        }

        void removeChild(Entity child, bool destroy_handle = false)
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

        inline std::vector<entt::entity>& getChildrenHandles()
        {
            return getComponent<ChildrenHandles>();
        }

        template<typename T, typename... Args>
        inline T& addComponent(Args&&... args)
        {
            if (hasComponent<T>()) DEX_LOG_ERROR("Entity already has that component!");

            return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
        }

        template <typename T>
        inline void removeComponent()
        {
            m_Scene->m_Registry.remove<T>(m_Handle);
        }

        template <typename T>
        inline T& getComponent()
        {
            return m_Scene->m_Registry.get<T>(m_Handle);
        }

        template <typename T>
        inline bool hasComponent()
        {
            return m_Scene->m_Registry.has<T>(m_Handle);
        }

        operator entt::entity() const;
        bool operator==(const Entity& other);
    private:
        const entt::entity m_Handle;
        Scene* m_Scene = nullptr;

        friend Scene;
    };
}
