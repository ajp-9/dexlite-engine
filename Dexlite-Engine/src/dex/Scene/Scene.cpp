#include "Scene.hpp"

#include "../Core/Engine.hpp"
#include "Entity/Entity.hpp"
#include "../Renderer/Shader/ShaderManager.hpp"
#include "../Util/Logging.hpp"

namespace dex
{
    Scene::Scene() 
    {
        m_Root = std::make_unique<Entity>(this, "Scene", false);
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
        //m_Root->updateChildrenTransform();
        //DEX_LOG_INFO("{}", m_Root->getComponent<ChildrenHandles>().size());

        for (auto& e : m_Entities)
        {
            e.updateChildrenTransform();
        }
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
