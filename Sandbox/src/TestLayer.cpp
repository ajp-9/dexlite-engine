#include "TestLayer.hpp"

#include <iostream>
#include <memory>

#include <nim/Application/Layer/Event/KeyEvent.hpp>

void TestLayer::attach()
{
}

void TestLayer::detach()
{
}

void TestLayer::update()
{
}

void TestLayer::render()
{
}

void TestLayer::event(std::unique_ptr<nim::event::Event>& e)
{
	std::cout << static_cast<nim::event::KeyEvent*>(e.get())->m_KeyCode << "\n";
}
