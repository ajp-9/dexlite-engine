#include "SandBox.hpp"

#include "TestLayer.hpp"
#include "SecondLayer.hpp"
#include <iostream>
#include <nim/Scene/Scene.hpp>
#include <nim/Scene/Component/RenderableComponent.h>
#include <nim/Scene/Entity/Entity.hpp>

void SandBox::begin()
{
	m_EngineHandle->getLayerManager().pushLayer(std::make_shared<TestLayer>());
	m_EngineHandle->getLayerManager().pushLayer(std::make_shared<SecondLayer>());

	nim::Scene scene;
	auto& entity = scene.createEntity();
	entity.addComponent<nim::component::Renderable>();

	scene.doRender();
}

void SandBox::end()
{
}

void SandBox::update()
{
}

void SandBox::render()
{
}
