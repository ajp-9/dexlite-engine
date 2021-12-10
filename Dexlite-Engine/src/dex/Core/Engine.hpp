#pragma once

#include "../Util/Time/Time.hpp"
#include "../Application/Window/Window.hpp"
#include "../Application/Layer/LayerManager.hpp"
#include "../Renderer/Renderer.hpp"
#include "Program/Program.hpp"
#include "Program/EntryPoint.hpp"
#include "Config.hpp"

namespace dex
{
    // Core engine.
    class Engine
    {
        static void Init(std::shared_ptr<Program> program);
        static void Shutdown();

        static void Run();
    public:
        static void Stop();

        static Window window;
        static Renderer renderer;
        static Layer::Manager layerManager;

        static Time time;

        friend int ::main(int argc, char** argv);
    private:
        static bool s_Running;

        // Is a unique ptr because of inheritance.
        static std::shared_ptr<Program> s_Program;
    };
}

using dex::Engine;
