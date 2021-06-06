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
        
        Renderer::Init(glm::uvec4(0, 0, s_Window.getDimensions()));
    }

    void Engine::Shutdown()
    {
        s_LayerManager.detachAllLayers();
        s_Program->Shutdown();
        Renderer::Shutdown();
    }
    
    void Engine::Run()
    {
        s_Program->Init();

        s_Running = true;

        while (s_Running)
        {
            s_DeltaTime.start();

            // Updating/events -------------
            s_Program->update();
            s_LayerManager.updateLayers();
            s_LayerManager.sendEvents();

            // Rendering ------------
            Renderer::clear();
            Renderer::beginFrame();

            s_Program->render();

            s_LayerManager.renderLayers();

            Renderer::endFrame();

            // Swap buffers when FINISHED rendering
            s_Window.update();

            s_DeltaTime.sleep();
            s_DeltaTime.end();

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

    DeltaTime Engine::s_DeltaTime(60);
    Window Engine::s_Window(glm::uvec2(1280, 720));

    Layer::Manager Engine::s_LayerManager;

    std::shared_ptr<Program> Engine::s_Program;
}
