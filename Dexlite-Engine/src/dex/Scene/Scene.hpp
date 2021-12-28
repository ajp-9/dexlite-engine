#pragma once

#include <entt.hpp>

namespace dex
{
    class Entity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity createEntity();
        void destroyEntity(Entity entity);

        void update();
        void physics();

        // Lambda must have "std::vector<dex::Entity>& entities" as its sole argument.
        template <typename F>
        void doCustumUpdate(F custom_update_func)
        {
            //custom_update_func(*this);
        }

        void findNSetActiveCamera();
    private:
        entt::registry m_Registry;
        entt::entity m_ActiveCameraID = entt::null;

        std::unique_ptr<Entity> m_Root;

        std::vector<Entity> m_Entities;
        
        friend class Entity;
        friend class Renderer;
    };
}
