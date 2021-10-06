#include "SandBox.hpp"

#include "Layers/WorldLayer.hpp"

#include <entt.hpp>

#include <iostream>

#include <dex/Scene/Component/TransformComponent.hpp>
#include "Layers/DebugLayer.hpp"
#include <imgui/imgui.h>
#include <dex/Scene/Component/ModelComponent.hpp>
#include <dex/Util/Logging.hpp>
#include <dex/Renderer/Model/ModelLoader.hpp>

using dex::Engine;

void SandBox::Init()
{
    Engine::layerManager.pushLayer(std::make_shared<WorldLayer>());
    Engine::layerManager.pushLayer(std::make_shared<DebugLayer>());
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
