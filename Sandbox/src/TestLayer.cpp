#include "TestLayer.hpp"

#include <iostream>
#include <memory>

#include <zim/Application/Layer/Event/KeyEvent.hpp>
#include <zim/Application/Layer/Event/MouseEvent.hpp>
#include <glm/vec2.hpp>

void TestLayer::Attach() {}

void TestLayer::Detach() {}

void TestLayer::update()
{
}

void TestLayer::render()
{
}

void TestLayer::event(std::unique_ptr<zim::Event::Event>& e)
{
	/*if(e->m_Type == zim::event::type::MOUSE_MOVE)
		std::cout << (int)e->getSelfSubstruct<zim::event::MouseEvent>().m_MousePosition.x << ", " << (int)e->getSelfSubstruct<zim::event::MouseEvent>().m_MousePosition.y << "\n";
	zim::event::MouseEvent et = e->getSelfSubstruct<zim::event::MouseEvent>();
	e->m_Handled = true;*/
}
