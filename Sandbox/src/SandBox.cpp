#include "SandBox.hpp"

#include "Layers/WorldLayer.hpp"

#include <entt.hpp>

#include <iostream>

#include <imgui/imgui.h>
#include <dex/Util/Logging.hpp>

using dex::Engine;

void SandBox::SetEngineConfig()
{
    EngineConfig.WindowTitle = "Sandbox";
}

void SandBox::Init()
{
    Engine::LayerManager.pushLayer(std::make_shared<WorldLayer>());
}

void SandBox::Shutdown()
{

}

void SandBox::update()
{

}

void SandBox::render()
{

}
