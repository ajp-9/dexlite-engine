#pragma once

#include <memory>
#include <dex/Dexlite.hpp>

#include "World/World.hpp"
#include "GUI/GUI.hpp"

class SandBox : public dex::Program
{
    dex::Window Window = { "Sandbox", glm::uvec2(1280, 800) };
    dex::Renderer Renderer = { Window };
    dex::Time Time;
public:
    SandBox();
    ~SandBox();
    
    virtual void beginFrame() override;

    virtual void update() override;
    virtual void render() override;

    virtual void endFrame() override;
private:
    World m_World;
    GUI m_GUI = { &m_World };
};

DEXLITE_DEFINE_MAIN(SandBox);
