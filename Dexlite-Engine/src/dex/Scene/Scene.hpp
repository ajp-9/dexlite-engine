#pragma once

#include <entt.hpp>

namespace dex
{
    class Entity;
    class Scene;

    using CustomSceneUpdate = void(Scene& scene);

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity createEntity();
        void destroyEntity(Entity entity);

        void update();
        void physics();

        void findNSetActiveCamera();
    private:
        entt::registry m_Registry;
        entt::entity m_ActiveCameraID = entt::null;

        std::unique_ptr<Entity> m_Root;

        std::vector<Entity> m_Entities;

        std::vector<CustomSceneUpdate*> m_CustomSceneUpdates;
    public:
        friend class Entity;
        friend class Renderer;
    };
}
