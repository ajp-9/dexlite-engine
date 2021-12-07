#pragma once

#include <entt.hpp>

#include "Component/CameraComponent.hpp"


namespace dex
{
    class Entity;

    // Custom Update Lambda
    typedef void (*CustomUpdate)(std::vector<dex::Entity> entities);

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity createEntity();
        void destroyEntity(Entity entity);

        void update();
        void physics();

        // Lambda must have "std::vector<Entity>& entities" as its sole argument.
        template <typename F>
        void doCustumUpdate(F func)
        {
            func(m_Entities);
        }

        void findNSetActiveCamera();
    private:
        entt::registry m_Registry;
        entt::entity m_ActiveCameraID;

        std::vector<Entity> m_Entities;
        
        friend class Entity;
        friend class Renderer;
    };
}
