#pragma once

#include <entt.hpp>

#include "../Renderer/Shader/ShaderGlobalUniforms.hpp"

namespace dex
{
    class Entity;
    class Scene;

    using SetGlobalShaderUniformsLambda = void(Scene& scene, entt::registry& scene_registry, Shader::GlobalUniforms& global_uniforms);
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

        entt::entity getActiveCameraID() { return m_ActiveCameraID; }

        // maybe mode to its own manager
        static void addSetGlobalShaderUniformsLambda(SetGlobalShaderUniformsLambda* lambda) { m_SetGlobalShaderUniformsLambdas.push_back(lambda); }
        static void addRenderModelLambda(RenderModelLambda* lambda) { m_RenderModelLambdas.push_back(lambda); }
    private:
        void findAndSetActiveCamera();
    private:
        entt::registry m_Registry;

        std::unique_ptr<Entity> m_Root;
        std::vector<Entity> m_Entities;
        entt::entity m_ActiveCameraID = entt::null;

        Shader::GlobalUniforms m_GlobalShaderUniforms;

        static std::vector<SetGlobalShaderUniformsLambda*> m_SetGlobalShaderUniformsLambdas;
        static std::vector<RenderModelLambda*> m_RenderModelLambdas;
    public:
        friend class Entity;
        friend class Renderer;
    };
}
