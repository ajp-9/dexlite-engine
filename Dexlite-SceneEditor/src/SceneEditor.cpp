#include "SceneEditor.hpp"

#include <imgui/imgui.h>
#include <memory>
#include "GUI/GUI.hpp"

namespace dex
{
    SceneEditor::SceneEditor()
    {
    }

    void SceneEditor::beginFrame()
    {
        Renderer.beginFrame();
        Renderer.clear(glm::vec4(.1, .1, .1, 1.0f));
    }

    void SceneEditor::update()
    {
        Time.doCycle();

        m_GUI.update(Time.getDeltaTime());
        m_CurrentScene.update(Time.getDeltaTime());
    }

    void SceneEditor::render()
    {
        m_GUI.render();
    }

    void SceneEditor::endFrame()
    {
        Renderer.endFrame();

        Window.swapBuffers();

        Time.sleep();

        Window.Input.pollNewEvents();

        if (!Window.Open)
            Running = false;
    }
}
