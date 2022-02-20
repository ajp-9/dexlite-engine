#include "SceneEditor.hpp"

#include <json.hpp>
#include <imgui/imgui.h>
#include <memory>
#include "GUI/GUI.hpp"
#include <fstream>

namespace dex
{
    SceneEditor::SceneEditor()
    {
        {
            std::ofstream out_bin = std::ofstream("out.bin", std::ios::binary);

            const uint32 w[] = { 0xffff };
            out_bin.write((char*)w, 2);
        }

        {
            std::ifstream in_bin = std::ifstream("out.bin", std::ios::binary);

            std::vector<uint8> buffer(std::istreambuf_iterator<char>(in_bin), {});
        }
    }

    void SceneEditor::beginFrame()
    {
        m_Renderer.beginFrame();
        //Renderer.clear(glm::vec4(.1, .1, .1, 1.0f));
    }

    void SceneEditor::update()
    {
        Time.doCycle();

        if (m_Window.Input.isKeyPressed(Event::Key::F11))
            if (!m_Window.isFullscreen())
                m_Window.setFullscreen();
            else
                m_Window.setWindowed();

        m_GUI.update(Time.getDeltaTime());
        m_CurrentScene.update(Time.getDeltaTime());
    }

    void SceneEditor::render()
    {
        m_GUI.render();
    }

    void SceneEditor::endFrame()
    {
        m_Renderer.endFrame();

        m_Window.swapBuffers();

        Time.sleep();

        m_Window.Input.pollNewEvents();

        if (!m_Window.Open)
            Running = false;
    }
}
