#include "Scene.hpp"

#include "../Core/Engine.hpp"
#include "Entity/Entity.hpp"
#include "Component/TagComponent.hpp"
#include "Component/ModelComponent.hpp"
#include "Component/TransformComponent.hpp"
#include "../Renderer/Shader/ShaderManager.hpp"
#include "../Util/Logging.hpp"

namespace dex
{
    Scene::Scene() {}

    Scene::~Scene() {}

    Entity Scene::createEntity()
    {
        Entity entity = Entity(m_Registry.create(), this);
        entity.addComponent<Component::Tag>();
        entity.addComponent<Component::Transform>();

        return entity;
    }

    void Scene::destroyEntity(Entity entity)
    {
        m_Registry.destroy(entity);
    }

    void Scene::update()
    {

    }

    void Scene::physics()
    {
    }

    void Scene::findNSetActiveCamera()
    {
        auto& cameraView = m_Registry.view<Component::Camera>();

        if (cameraView.size() == 1)
        {
            for (auto& eID : cameraView)
            {
                if (m_Registry.get<Component::Camera>(eID).m_IsEnabled)
                    m_ActiveCameraID = eID;
            }
        }
        else if (cameraView.size() > 1)
        {
            DEX_LOG_ERROR("<Scene::findNSetMainCamera>: Too many main cameras.");
        }
        else if (cameraView.size() < 1)
        {
            DEX_LOG_ERROR("<Scene::findNSetMainCamera>: No cameras found.");
        }
    }
}
