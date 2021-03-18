#include "SandBox.hpp"

#include "TestLayer.hpp"

void SandBox::begin()
{
	m_EngineHandle->getLayerManager().pushLayer(std::make_shared<TestLayer>());
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
