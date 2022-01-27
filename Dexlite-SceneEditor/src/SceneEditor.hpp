#pragma once

#include <dex/Dexlite.hpp>
#include "GUI/GUI.hpp"

// Todo:
// - Rehaul layer system

namespace dex
{
    class SceneEditor : public dex::Program
    {
        dex::Window Window = { "Dexlite Scene-Editor", glm::uvec2(1280, 800) };
        dex::Renderer Renderer = { Window };
        dex::Time Time;
    public:
        SceneEditor();
        //~SceneEditor();

        virtual void beginFrame() override;

        virtual void update() override;
        virtual void render() override;

        virtual void endFrame() override;
    private:
        CurrentScene m_CurrentScene = { &Window, &Renderer };

        GUI m_GUI = GUI(&Renderer, &m_CurrentScene);
    };
}

DEXLITE_DEFINE_MAIN(dex::SceneEditor);
