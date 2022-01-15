#pragma once

#include <memory>
#include <dex/Dexlite.hpp>

#include "World/WorldLayer.hpp"

class SandBox : public dex::Program
{
    dex::Window Window = { "Sandbox", glm::uvec2(1280, 800) };
    dex::Renderer Renderer = { Window.Handle };
    dex::Time Time;
public:
    SandBox();
    ~SandBox();
    
    virtual void beginFrame() override;
    virtual void update() override;
    virtual void render() override;
    virtual void endFrame() override;
private:
    WorldLayer m_WorldLayer;
};

DEXLITE_DEFINE_MAIN(SandBox);
