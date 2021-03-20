#include "Scene.hpp"

#include "Component/RenderableComponent.h"
#include "Entity/Entity.hpp"

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

    void Scene::doUpdate()
    {
        
    }

    void Scene::doPhysics()
    {
    }

    void Scene::doRender()
    {
        auto& view = m_Registry.view<component::Renderable>();
        for (auto& entity : view)
        {
            m_Registry.get<component::Renderable>(entity).render();
        }
    }

    template<typename T>
    inline void Scene::doCustumUpdate()
    {

    }
}
