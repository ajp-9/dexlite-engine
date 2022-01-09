#include "Scene.hpp"

#include "../Core/Engine.hpp"
#include "Entity/Entity.hpp"
#include "../Renderer/Shader/ShaderManager.hpp"
#include "Component/Camera/CameraComponent.hpp"
#include "Component/LightComponents.hpp"
#include "../Util/Logging.hpp"
#include "../Scene/Component/Model/ModelComponent.hpp"
#include "Component/Camera/CameraComponent.hpp"
#include "Component/LightComponents.hpp"

namespace dex
{
    Scene::Scene()
    {
        m_Root = std::make_unique<Entity>(this, "Scene", false);


        // REEEE MORE THAN 1 INSTANCE => sceneManager

        // Default model component rendering lambda.

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
            // Camera:

            m_GlobalShaderUniforms.setCameraPosition(m_Registry.get<Component::Transform>(m_ActiveCameraID).getTransformationMatrix()[3]);

            if (Engine::Renderer.m_ChangeProjectionMatrixNext)
                m_Registry.get<Component::Camera>(m_ActiveCameraID).updateProjectionMatrix();

            // if proj or view changed for perf
            m_GlobalShaderUniforms.setProjectionViewMatrix(m_Registry.get<Component::Camera>(m_ActiveCameraID).getProjectionViewMatrix());

            // Ambient Light:

            const auto& ambient_light_view = m_Registry.view<Component::Light::Ambient>();

            if (ambient_light_view.size() == 1)
            {
                for (auto& ambient_light_entity : ambient_light_view)
                    m_GlobalShaderUniforms.setAmbientLight(m_Registry.get<Component::Light::Ambient>(ambient_light_entity));
            }
            else if (ambient_light_view.size() > 1)
            {
                DEX_LOG_WARN("<dex::Scene::render()>: Only 1 ambient light per scene.");
            }

            // Directional Light:

            const auto& directional_light_view = m_Registry.view<Component::Light::Directional>();

            if (directional_light_view.size() == 1)
            {
                for (auto& directional_light_entity : directional_light_view)
                    m_GlobalShaderUniforms.setDirectionalLight(m_Registry.get<Component::Light::Directional>(directional_light_entity));
            }
            else if (directional_light_view.size() > 1)
            {
                DEX_LOG_WARN("<dex::Scene::render()>: Only 1 directional light per scene.");
            }

            // Point Lights:

            const auto& point_light_view = m_Registry.view<Component::Light::Point>();

            if (point_light_view.size() <= 5 && point_light_view.size() > 0)
            {
                std::vector<dex::Light::Point> point_lights;

                for (auto& point_light_entity : point_light_view)
                    point_lights.push_back(m_Registry.get<Component::Light::Point>(point_light_entity));

                m_GlobalShaderUniforms.setPointLights(point_lights);
            }
            else if (point_light_view.size() > 5)
            {
                DEX_LOG_WARN("<dex::Scene::render()>: Only 5 point lights per scene.");
            }

            // manager compares n uploads in loop
            Engine::Renderer.ShaderManager.updateCurrentGlobalShaderUniforms(m_GlobalShaderUniforms);

            m_GlobalShaderUniforms.setAllClean();

            for (auto render_model_lambda : Engine::SceneManager.m_Scene_RenderModel_Functions)
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
