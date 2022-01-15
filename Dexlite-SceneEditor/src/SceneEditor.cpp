#include "SceneEditor.hpp"

#include <imgui/imgui.h>
#include <memory>
#include "GUI/GUI_Layer.hpp"

namespace dex
{
    void SceneEditor::SetEngineConfig()
    {
        EngineConfig.WindowTitle = "Dexlite Scene-Editor";
    }

    void SceneEditor::Init()
    {
        //dex::Engine::Window.setFullscreen();
    }

    void SceneEditor::Shutdown() {}

    void SceneEditor::update()
    {
        m_GUI_Layer.update();
    }

    void SceneEditor::render()
    {
        m_GUI_Layer.render();
    }
}
