#include "SandBox.hpp"

#include "TestLayer.hpp"
#include "SecondLayer.hpp"
#include <iostream>
#include <nim/Scene/Scene.hpp>
#include <nim/Scene/Component/RenderableComponent.h>
#include <nim/Scene/Entity/Entity.hpp>

using nim::NimbleEngine;

void SandBox::Begin()
{
	NimbleEngine::m_Application.m_LayerManager.pushLayer(std::make_shared<TestLayer>());
	NimbleEngine::m_Application.m_LayerManager.pushLayer(std::make_shared<SecondLayer>());

	nim::Scene scene;
	auto& entity = scene.createEntity();
	entity.addComponent<nim::component::Renderable>();

	scene.doRender();
}

void SandBox::End()
{
}

void SandBox::update()
{
}

void SandBox::render()
{
}
