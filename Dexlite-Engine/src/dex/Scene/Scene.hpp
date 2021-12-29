#pragma once

#include <entt.hpp>

#include "../Renderer/Shader/ShaderGlobalUniforms.hpp"

namespace dex
{
    class Entity;
    class Scene;

    using RenderModelLambda = void(entt::registry& scene_registry);

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity createEntity();
        void destroyEntity(Entity entity);

        void update();
        void render();
        void physics();

        void addRenderModelLambda(RenderModelLambda* lambda) { m_RenderModelLambdas.push_back(lambda); }
    private:
        void findAndSetActiveCamera();
    private:
        entt::registry m_Registry;

        std::unique_ptr<Entity> m_Root;
        std::vector<Entity> m_Entities;
        entt::entity m_ActiveCameraID = entt::null;

        Shader::GlobalUniforms m_ShaderGlobalUniforms;

        std::vector<RenderModelLambda*> m_RenderModelLambdas;
    public:
        friend class Entity;
        friend class Renderer;
    };
}
