#pragma once

#include <dex/Dexlite.hpp>
#include "GUI/GUI.hpp"

// Todo:
// - Rehaul layer system

namespace dex
{
    class SceneEditor : public dex::Program
    {
    public:
        SceneEditor();
        //~SceneEditor();

        virtual void beginFrame() override;
        
        virtual void update() override;
        virtual void render() override;

        virtual void endFrame() override;
    private:
        dex::Window m_Window = { "Dexlite Scene-Editor", glm::uvec2(1280, 800) };
        dex::Renderer m_Renderer = { m_Window };
        dex::Time Time;
    private:
        CurrentScene m_CurrentScene = { &m_Window, &m_Renderer };

        GUI m_GUI = GUI(&m_Window, &m_Renderer, &m_CurrentScene, &Running);
    };
}

DEXLITE_DEFINE_MAIN(dex::SceneEditor);
