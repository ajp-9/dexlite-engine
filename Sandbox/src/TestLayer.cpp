#include "TestLayer.hpp"

#include <iostream>
#include <memory>

#include <nim/Application/Layer/Event/KeyEvent.hpp>
#include <nim/Application/Layer/Event/MouseEvent.hpp>
#include <glm/vec2.hpp>

void TestLayer::Attach() {}

void TestLayer::Detach()
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
	/*if(e->m_Type == nim::event::type::MOUSE_MOVE)
		std::cout << (int)e->getSelfSubstruct<nim::event::MouseEvent>().m_MousePosition.x << ", " << (int)e->getSelfSubstruct<nim::event::MouseEvent>().m_MousePosition.y << "\n";
	nim::event::MouseEvent et = e->getSelfSubstruct<nim::event::MouseEvent>();
	e->m_Handled = true;*/
}
