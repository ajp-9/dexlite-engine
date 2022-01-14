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
        m_GUI_Layer = std::make_shared<GUI_Layer>(m_CurrentScene, m_ViewportCamera);
        dex::Engine::LayerManager.pushLayer(m_GUI_Layer);


        //m_GUI_Layer->setScene(m_CurrentScene);
        //m_GUI_Layer->setViewportCamera(m_ViewportCamera);

        //dex::Engine::Window.setFullscreen();
    }

    void SceneEditor::Shutdown() {}

    void SceneEditor::update()
    {

    }

    void SceneEditor::render()
    {
    }
}
