#pragma once

#include <entt.hpp>

#include "../Renderer/Shader/ShaderGlobalUniforms.hpp"

namespace dex
{
    class Entity;
    class Scene;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity createEntity();
        void destroyEntity(Entity entity);

        void update();
        void render(const glm::vec2& viewport_size);
        void physics();

        entt::entity getActiveCameraID() { return m_ActiveCameraID; }
    private:
        void findAndSetActiveCamera();
    private:
        entt::registry m_Registry;

        std::unique_ptr<Entity> m_Root;
        std::vector<Entity> m_Entities;
        entt::entity m_ActiveCameraID = entt::null;

        Shader::GlobalUniforms m_GlobalShaderUniforms;
    public:
        friend class Entity;
        friend class Renderer;
    };
}
