#pragma once

#include "Scene.hpp"
#include "Entity/Entity.hpp"

namespace dex
{
    using Scene_RenderModel_Function = void(entt::registry& scene_registry);
    using Entity_UpdateComponentWithTransform_Function = void(Entity& entity);

    class SceneManager
    {
    public:
        SceneManager();

        void addScene_RenderModel_Function(Scene_RenderModel_Function* func) { m_Scene_RenderModel_Functions.push_back(func); }
        void addEntity_UpdateComponentWithTransform_Function(Entity_UpdateComponentWithTransform_Function* func) { m_Entity_UpdateComponentWithTransform_Functions.push_back(func); }
    private:
        std::vector<Scene_RenderModel_Function*> m_Scene_RenderModel_Functions;

        std::vector<Entity_UpdateComponentWithTransform_Function*> m_Entity_UpdateComponentWithTransform_Functions;
    public:
        friend Scene;
        friend Entity;
    };
}
