#pragma once

#include <entt.hpp>
#include "../Renderer/Shader/ShaderGlobalUniforms.hpp"

namespace dex
{
    class Entity;
    class Scene;
    class Renderer;
    class Physics;

    class Scene
    {
    public:
        Scene(Renderer* renderer, Physics* physics);
        ~Scene();

        Scene(const Scene& other) = delete;
        const Scene& operator=(const Scene& other) = delete;

        Scene(Scene&& other) noexcept;
        Scene& operator=(Scene&& other) noexcept;

        Entity createEntity();
        void destroyEntity(Entity entity);

        void update();
        void render(const glm::vec2& viewport_size, Renderer& renderer, entt::entity camera = entt::null);
        void physics(Physics* physics);

        Entity getEntity(const std::string& tag);

        entt::entity getActiveCameraID() { return m_ActiveCameraID; }
    private:
        void findAndSetActiveCamera();
    private:
        Renderer* m_Renderer;
        Physics* m_Physics;

        entt::registry m_Registry;

        std::vector<Entity> m_Entities;
        entt::entity m_ActiveCameraID = entt::null;

        Shader::GlobalUniforms m_GlobalShaderUniforms;
    public:
        std::unique_ptr<Entity> Root;
    public:
        friend class Entity;
        friend class Renderer;
    };
}
