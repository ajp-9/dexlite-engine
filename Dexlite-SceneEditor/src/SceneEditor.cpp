#include "SceneEditor.hpp"

#include <json.hpp>
#include <imgui/imgui.h>
#include <memory>
#include "GUI/GUI.hpp"

namespace dex
{
    SceneEditor::SceneEditor()
    {
        nlohmann::json j;
        j["wat"] = 4;
        auto& e = j["a"];
        e["b"] = 1;
        e["c"] = { 3, 2, 5.432, 1 };
        std::cout << j["a"]["c"] << '\n';

        m_CurrentScene.Scene.getEntity("Player").addNewChild("wot");
        std::cout << glGetString(GL_VERSION) << '\n';
    }

    void SceneEditor::beginFrame()
    {
        Renderer.beginFrame();
        //Renderer.clear(glm::vec4(.1, .1, .1, 1.0f));
    }

    void SceneEditor::update()
    {
        Time.doCycle();

        if (Window.Input.isKeyPressed(Event::Key::F11))
            if (!Window.isFullscreen())
                Window.setFullscreen();
            else
                Window.setWindowed();

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
