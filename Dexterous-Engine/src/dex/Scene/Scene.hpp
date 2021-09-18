#pragma once

#include <entt.hpp>

#include "Component/CameraComponent.hpp"

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
        template <typename T>
        void doCustumUpdate() {}

        void findNSetMainCamera();
    private:
        entt::registry m_Registry;
        entt::entity m_MainCameraID;
        
        friend class Entity;
        friend class Renderer;
    };
}
