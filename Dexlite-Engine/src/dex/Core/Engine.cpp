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
        LayerManager.detachAllLayers();
        s_Program->Shutdown();
    }
    
    void Engine::Run()
    {
        s_Program->Init();

        s_Running = true;

        while (s_Running)
        {
            Time.doCycle();

            // Updating/events -------------
            s_Program->update();
            
            LayerManager.updateLayers();
            LayerManager.sendEvents();

            // Rendering -------------------
            Renderer.clear();
            Renderer.beginFrame();

            s_Program->render();

            LayerManager.renderLayers();

            Renderer.endFrame();

            // Swap buffers when FINISHED rendering & reset event queue 
            Window.update();

            Time.sleep();

            if (!s_Running)
                break;
        }
    }

    void Engine::Stop()
    {
        s_Running = false;
    }

    /*
    ** Initialize static member variables:
    */

    bool Engine::s_Running;
    //1280 720
    Window Engine::Window(glm::uvec2(720, 720));
    Renderer Engine::Renderer;
    Layer::Manager Engine::LayerManager;
    SceneManager Engine::SceneManager;

    Time Engine::Time(60);

    std::shared_ptr<Program> Engine::s_Program;
}
