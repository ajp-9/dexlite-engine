#include "Scene.hpp"

#include "Entity/Entity.hpp"
#include "Component/ModelComponent.hpp"
#include "Component/TransformComponent.hpp"

namespace nim
{
    Scene::Scene() {}

    Scene::~Scene() {}

    Entity Scene::createEntity()
    {
        return Entity(m_Registry.create(), this);
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

    void Scene::render()
    {
        auto& view = m_Registry.view<Component::Model, Component::Transform>();

        for (auto& eID : view)
        {
            Component::Model model = m_Registry.get<Component::Model>(eID);

            model.m_Shader.lock()->bind();
            model.m_Shader.lock()->setModelMatrix(m_Registry.get<Component::Transform>(eID));

            model.render();
        }
    }
}
