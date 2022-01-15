#pragma once

#include "../Util/Time/Time.hpp"
#include "../Application/Window/Window.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Scene/SceneManager.hpp"

#include "Program/Program.hpp"
#include "Program/EntryPoint.hpp"

namespace dex
{
    // Core engine.
    template <class P>
    class Engine
    {
    public:
        Engine()
        {
            SceneManager::setDefaults();
        }

        void Run()
        {
            while (Program.Running)
            {
                Program.beginFrame();

                Program.update();
                Program.render();

                Program.endFrame();
            }
        }
    private:
        P Program;
    };
}
