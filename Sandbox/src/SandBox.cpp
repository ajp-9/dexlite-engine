#include "SandBox.hpp"

#include "Layers/WorldLayer.hpp"

#include <entt.hpp>

#include <iostream>

#include "Layers/DebugLayer.hpp"
#include <imgui/imgui.h>
#include <dex/Util/Logging.hpp>

using dex::Engine;

void SandBox::Init()
{
    Engine::LayerManager.pushLayer(std::make_shared<WorldLayer>());
    Engine::LayerManager.pushLayer(std::make_shared<DebugLayer>());
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
