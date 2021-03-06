#pragma once

#include <iostream>
#include <entt.hpp>

#include "../../Util/Logging.hpp"
#include "../Scene.hpp"

namespace dex
{
    // Does not need to be a shared pointer, since its small contents (handle ID and ptr to registry) would remain constant between its instances.
    class Entity
    {
    public:
        Entity() = default;
        // Creates a new entity, and adds it to the scene's entity vector.
        Entity(Scene* scene, std::string tag = "", bool add_to_root = true);
        // Creates a new class from a pre-existing entity handle.
        Entity(entt::entity handle, Scene* scene);

        // Destroys the handle and its children's handle in the registry. This class would remain intact and should be disgarded afterwards.
        void destroy();
        
        // Destroys all its children in the registry. Their classes would remain intact and should be disgarded afterwards.
        void destroyChildren();

        Entity addNewChild(std::string tag = "")
        {
            Entity child = { m_Scene, tag, false};
            addChild(child);

            return child;
        }

        void addChild(Entity child);

        void removeChild(Entity child, bool destroy_handle = false);

        //std::vector<entt::entity>& getChildrenHandles() const;
        std::vector<Entity>& getChildren() const;

        void updateChildrenTransform();

        bool hasParent()
        {
            return getParent().m_Handle != entt::null;
        }

        void setParent(Entity parent);

        Entity& getParent();

        template<typename T, typename... Args>
        T& addComponent(Args&&... args)
        {
            //typedef comp
            if (hasComponent<T>()) DEX_LOG_ERROR("<dex::Entity::addComponent()>: Entity already has that component!");
            
            return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
        }

        template <typename T>
        void removeComponent()
        {
            m_Scene->m_Registry.remove<T>(m_Handle); 
        }

        template <typename T>
        T& getComponent() const
        { 
            return m_Scene->m_Registry.get<T>(m_Handle);
        }

        template <typename T>
        bool hasComponent() const
        { 
            return m_Scene->m_Registry.has<T>(m_Handle);
        }

        const bool isValid() const { return m_Scene->m_Registry.valid(m_Handle); };

        const entt::entity& getHandle() const { return m_Handle; }
        
        operator entt::entity() const { return m_Handle; };
        const bool operator==(const Entity& other) const { return m_Handle == other.m_Handle && m_Scene == other.m_Scene; }
    private:
        entt::entity m_Handle = entt::null;
        Scene* m_Scene = nullptr;
    public:
        friend class Scene;
    };
}
