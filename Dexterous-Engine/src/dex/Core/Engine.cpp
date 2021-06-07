#include "Engine.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include "Program/Program.hpp"

namespace dex
{
    void Engine::Init(std::shared_ptr<Program> program)
    {
        s_Program = program;
    }

    void Engine::Shutdown()
    {
        layerManager.detachAllLayers();
        s_Program->Shutdown();
    }
    
    void Engine::Run()
    {
        s_Program->Init();

        s_Running = true;

        while (s_Running)
        {
            deltaTime.start();

            // Updating/events -------------
            s_Program->update();
            layerManager.updateLayers();
            layerManager.sendEvents();

            // Rendering ------------
            renderer.clear();
            renderer.beginFrame();

            s_Program->render();

            layerManager.renderLayers();

            renderer.endFrame();

            // Swap buffers when FINISHED rendering & reset event queue 
            window.update();

            deltaTime.sleep();
            deltaTime.end();

            if (!s_Running)
                Shutdown();
        }
    }

    void Engine::Stop()
    {
        s_Running = false;
    }

    /*
    ** Initialize member variables
    */

    bool Engine::s_Running;

    Window Engine::window(glm::uvec2(1280, 720));
    Renderer Engine::renderer = { glm::uvec4(0, 0, 600, 300) };
    Layer::Manager Engine::layerManager;

    DeltaTime Engine::deltaTime(60);

    std::shared_ptr<Program> Engine::s_Program;
}
