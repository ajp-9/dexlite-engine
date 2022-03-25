#include "SceneEditor.hpp"

#include <json.hpp>
#include <imgui/imgui.h>
#include <memory>
#include "GUI/GUI.hpp"
#include <fstream>
#include <iostream>

namespace dex
{
    SceneEditor::SceneEditor()
    {
        Physics phys;

        {
            std::ofstream out_bin = std::ofstream("out.bin", std::ios::binary);

            //float wat = .32723235;
            //const uint32 val = *reinterpret_cast<int*>(&wat);
            
            uint32 val = 0xdeadbeef;
            
            uint8 buffer[4];
            buffer[0] = (val & 0xFF000000) >> (8 * 3);
            buffer[1] = (val & 0x00FF0000) >> (8 * 2);
            buffer[2] = (val & 0x0000FF00) >> (8 * 1);
            buffer[3] = (val & 0x000000FF) >> (8 * 0);

            out_bin.write((char*)buffer, 4);
        }
        
        {
            std::ifstream in_bin = std::ifstream("out.bin", std::ios::binary);

            std::vector<uint8> buffer(std::istreambuf_iterator<char>(in_bin), {});

            int val = 0;
            val |= (buffer[0]) << (8 * 3);
            val |= (buffer[1]) << (8 * 2);
            val |= (buffer[2]) << (8 * 1);
            val |= (buffer[3]) << (8 * 0);

            std::cout << std::setprecision(12) <<  *reinterpret_cast<float*>(&val) << '\n';
            //std::cout << std::setprecision(9) << (double).32746823235 << '\n';
            std::cout << std::hex << val << '\n';
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
        m_Physics.update();

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
