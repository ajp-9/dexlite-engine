#pragma once

#include <dex/Dexlite.hpp>
#include "GUI/GUI_Layer.hpp"

// Todo:
// - Rehaul layer system

namespace dex
{
    class SceneEditor : public dex::Program
    {
    public:
        virtual void SetEngineConfig() override;

        virtual void Init() override;
        virtual void Shutdown() override;

        virtual void update() override;
        virtual void render() override;
    private:
        std::shared_ptr<Scene> m_CurrentScene = std::make_shared<Scene>();
        std::shared_ptr<Entity> m_ViewportCamera = std::make_shared<Entity>(&*m_CurrentScene, "Editor Camera", false);

        GUI_Layer m_GUI_Layer = GUI_Layer(m_CurrentScene, m_ViewportCamera);
    };
}

DEXLITE_DEFINE_MAIN(dex::SceneEditor);
