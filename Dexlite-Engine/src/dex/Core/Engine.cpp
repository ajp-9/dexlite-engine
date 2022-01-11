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

        s_Program->SetEngineConfig();

        Window.setTitle(s_Program->EngineConfig.WindowTitle);
        Window.setSize(s_Program->EngineConfig.WindowSize);

        s_Program->Init();
    }

    void Engine::Shutdown()
    {
        LayerManager.detachAllLayers();
        s_Program->Shutdown();
    }
    
    void Engine::Run()
    {
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

    void Engine::updateConfig()
    {
        const auto& config = s_Program->EngineConfig;

        // set window dimensions title etc
    }

    /*
    ** Initialize static member variables:
    */

    std::shared_ptr<Program> Engine::s_Program;

    bool Engine::s_Running;
    //1280 720
    Window Engine::Window;
    Renderer Engine::Renderer;
    Layer::Manager Engine::LayerManager;
    SceneManager Engine::SceneManager;

    Time Engine::Time(60);
}
