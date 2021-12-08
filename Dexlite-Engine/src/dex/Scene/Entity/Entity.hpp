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
    public:
        // Creates a new entity, and adds it to the scene's entity vector.
        Entity(Scene* scene);
        // Creates a new class from a pre-existing entity handle.
        Entity(entt::entity handle, Scene* scene);

        // Destroys the handle in the registry. This class would remain intact and should be disgarded afterwards.
        void destroy();

        // Destroys all its children in the registry. Their classes would remain intact and should be disgarded afterwards.
        void destroyChildren();

        bool isEntityValid()
        {
            return m_Scene->m_Registry.valid(m_Handle);
        }

        Entity addNewChild();

        inline void addChild(Entity child)
        {
            getChildrenHandles().push_back(child.m_Handle); 
        };

        void addChild(entt::entity child_handle)
        { 
            getChildrenHandles().push_back(child_handle);
        }

        void removeChild(Entity child, bool destroy_handle = false);

        inline std::vector<entt::entity>& getChildrenHandles();

        void updateChildrenTransform()
        {
            if (getComponent<Component::Transform>().m_FlagChanged)
            {
                auto& children_handles = getChildrenHandles();

                for (entt::entity child_handle : children_handles)
                {
                    Component::Transform& child_transform = m_Scene->m_Registry.get<Component::Transform>(child_handle);

                    child_transform.setParentTransformationMatrix(getComponent<Component::Transform>().getTransformationMatrix());
                }

                getComponent<Component::Transform>().m_FlagChanged = false;
            }
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

        operator entt::entity() const { return m_Handle; };
        bool operator==(const Entity& other);
    private:
        const entt::entity m_Handle;
        Scene* m_Scene = nullptr;

        friend class Scene;
    };
}
