#pragma once

#include "../Util/Time/Time.hpp"
#include "../Application/Window/Window.hpp"
#include "../Application/Layer/LayerManager.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Scene/SceneManager.hpp"

#include "Program/Program.hpp"
#include "Program/EntryPoint.hpp"
#include "EngineConfig.hpp"

namespace dex
{
    // Core engine.
    class Engine
    {
        static std::shared_ptr<Program> s_Program;
    private:
        static void Init(std::shared_ptr<Program> program);
        static void Shutdown();

        static void Run();
    public:
        static void Stop();

        static void updateConfig();

        static Window Window;
        static Renderer Renderer;
        static Layer::Manager LayerManager;
        static SceneManager SceneManager;

        static Time Time;
    private:
        static bool s_Running;
    public:
        friend int ::main(int argc, char** argv);
    };
}

using dex::Engine;
