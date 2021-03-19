#include "TestLayer.hpp"

#include <iostream>
#include <memory>

#include <nim/Application/Layer/Event/KeyEvent.hpp>

#define PROFILE
#include <nim/Util/Profile.hpp>
#include <nim/Util/Timer.hpp>

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
	if(e->m_Type == nim::event::type::KEY_DOWN)
		std::cout << e->getSelfSubstruct<nim::event::KeyEvent>().m_KeyCode << "\n";

	e->m_Handled = true;
}
