#include "Scene.hpp"

#include "../Core/Engine.hpp"
#include "Entity/Entity.hpp"
#include "../Renderer/Shader/ShaderManager.hpp"
#include "Component/Camera/CameraComponent.hpp"
#include "../Util/Logging.hpp"
#include "../Scene/Component/ModelComponent.hpp"

namespace dex
{
    Scene::Scene()
    {
        m_Root = std::make_unique<Entity>(this, "Scene", false);

        // Default model component rendering lambda.
        addRenderModelLambda(
            [] (entt::registry& scene_registry)
            {
                const auto& model_view = scene_registry.view<Component::Model>();

                for (auto& entityID : model_view)
                {
                    auto& model = scene_registry.get<Component::Model>(entityID);
                    model.prepareRendering();
                    model.render();
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
            // manager compares n uploads
            Engine::Renderer.ShaderManager.updateCurrentGlobalShaderUniforms(m_ShaderGlobalUniforms);

            auto shader = Engine::Renderer.ShaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D);

            if (Engine::Renderer.m_ChangeProjectionMatrixNext)
                m_Registry.get<Component::Camera>(m_ActiveCameraID).updateProjectionMatrix();

            shader->setProjectionViewMatrix(m_Registry.get<Component::Camera>(m_ActiveCameraID).getProjectionViewMatrix());

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
}
