#include "Scene.hpp"

#include "../Core/Engine.hpp"
#include "Entity/Entity.hpp"
#include "../Renderer/Shader/ShaderManager.hpp"
#include "Component/Camera/CameraComponent.hpp"
#include "Component/LightComponents.hpp"
#include "../Util/Logging.hpp"
#include "../Scene/Component/Model/ModelComponent.hpp"

namespace dex
{
    Scene::Scene()
    {
        m_Root = std::make_unique<Entity>(this, "Scene", false);

        // Default model component rendering lambda.
        addRenderModelLambda(
            [](entt::registry& scene_registry)
            {
                const auto& model_view = scene_registry.view<Component::Model>();

                for (auto& entityID : model_view)
                {
                    auto& model = scene_registry.get<Component::Model>(entityID);
                    model.prepareRendering();
                    model.render();
                }
            });

        // why
        addSetGlobalShaderUniformsLambda(
            [](Scene& scene, entt::registry& scene_registry, Shader::GlobalUniforms& global_uniforms)
            {
                if (Engine::Renderer.m_ChangeProjectionMatrixNext)
                    scene_registry.get<Component::Camera>(scene.getActiveCameraID()).updateProjectionMatrix();

                global_uniforms.setProjectionViewMatrix(scene_registry.get<Component::Camera>(scene.getActiveCameraID()).getProjectionViewMatrix());
            });

        addSetGlobalShaderUniformsLambda(
            [](Scene& scene, entt::registry& scene_registry, Shader::GlobalUniforms& global_uniforms)
            {
                const auto& ambient_light_view = scene_registry.view<Component::Light::Ambient>();

                if (ambient_light_view.size() == 1)
                {
                    for (auto& ambient_light_entity : ambient_light_view)
                        global_uniforms.setAmbientLight(scene_registry.get<Component::Light::Ambient>(ambient_light_entity));
                }
                else if (ambient_light_view.size() > 1)
                {
                    DEX_LOG_WARN("<dex::Scene::render()>: Only 1 ambient light per scene.");
                }
            });

        addSetGlobalShaderUniformsLambda(
            [](Scene& scene, entt::registry& scene_registry, Shader::GlobalUniforms& global_uniforms)
            {
                const auto& ambient_light_view = scene_registry.view<Component::Light::Directional>();

                if (ambient_light_view.size() == 1)
                {
                    for (auto& ambient_light_entity : ambient_light_view)
                        global_uniforms.setDirectionalLight(scene_registry.get<Component::Light::Directional>(ambient_light_entity));
                }
                else if (ambient_light_view.size() > 1)
                {
                    DEX_LOG_WARN("<dex::Scene::render()>: Only 1 directional light per scene.");
                }
            });
    }

    Scene::~Scene() {}

    Entity Scene::createEntity()
    {
        return Entity(this);
    }

    void Scene::destroyEntity(Entity entity)
    {
        m_Registry.destroy(entity);
    }

    void Scene::update()
    {
        m_Root->updateChildrenTransform();
    }

    void Scene::render()
    {
        findAndSetActiveCamera();

        if (m_ActiveCameraID != entt::null)
        {
            m_GlobalShaderUniforms.setCameraPosition(m_Registry.get<Component::Transform>(m_ActiveCameraID).getTransformationMatrix()[3]);

            for (auto set_global_shader_uniforms_lambda : m_SetGlobalShaderUniformsLambdas)
                set_global_shader_uniforms_lambda(*this, m_Registry, m_GlobalShaderUniforms);

            // manager compares n uploads in loop
            Engine::Renderer.ShaderManager.updateCurrentGlobalShaderUniforms(m_GlobalShaderUniforms);

            m_GlobalShaderUniforms.setAllClean();

            for (auto render_model_lambda : m_RenderModelLambdas)
                render_model_lambda(m_Registry);
        }
        else
        {
            DEX_LOG_WARN("<dex::Renderer::renderScene()>: No active camera found.");
        }
    }

    void Scene::physics()
    {

    }

    void Scene::findAndSetActiveCamera()
    {
        const auto& cameraView = m_Registry.view<Component::Camera>();

        if (cameraView.size() == 1)
        {
            for (auto& eID : cameraView)
            {
                Entity entity = Entity(eID, this);

                if (entity.getComponent<Component::Camera>().IsEnabled)
                    m_ActiveCameraID = eID;
            }
        }
        else if (cameraView.size() > 1)
        {
            DEX_LOG_ERROR("<Scene::findNSetMainCamera>(): Too many main cameras.");
        }
        else if (cameraView.size() < 1)
        {
            DEX_LOG_ERROR("<Scene::findNSetMainCamera()>: No cameras found.");
        }
    }

    /*
    ** Initialize static member variables:
    */

    std::vector<SetGlobalShaderUniformsLambda*> Scene::m_SetGlobalShaderUniformsLambdas;
    std::vector<RenderModelLambda*> Scene::m_RenderModelLambdas;
}
