#include "SceneManager.hpp"

#include "../Util/Logging.hpp"
#include "Component/Model/ModelComponent.hpp"
#include "Component/Camera/CameraComponent.hpp"
#include "Component/LightComponents.hpp"

namespace dex
{
    SceneManager::SceneManager()
    {
        // Scene Default Lambdas:

        addScene_RenderModel_Function(
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

        // Entity Default Lambdas:

        addEntity_UpdateComponentWithTransform_Function(
            [](Entity& entity)
            {
                if (entity.hasComponent<Component::Camera>())
                {
                    auto& camera = entity.getComponent<Component::Camera>();

                    if (camera.IsEnabled)
                        camera.updateViewMatrix();
                }
            });

        addEntity_UpdateComponentWithTransform_Function(
            [](Entity& entity)
            {
                if (entity.hasComponent<Component::Light::Directional>())
                {
                    entity.getComponent<Component::Light::Directional>().Direction = entity.getComponent<Component::Transform>().getForward();
                }
            });

        addEntity_UpdateComponentWithTransform_Function(
            [](Entity& entity)
            {
                if (entity.hasComponent<Component::Light::Point>())
                {
                    entity.getComponent<Component::Light::Point>().Position = entity.getComponent<Component::Transform>().getWorldPosition();
                }
            });
    }
}
