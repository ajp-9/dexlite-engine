#pragma once

#include <dex/Dexlite.hpp>

#include "../../../CurrentScene/CurrentScene.hpp"

namespace dex
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel(CurrentScene* current_scene);

        void render();
    private:
        void renderEntityNode(Entity& entity);
    private:
        CurrentScene* m_CurrentScene;
    };
}
