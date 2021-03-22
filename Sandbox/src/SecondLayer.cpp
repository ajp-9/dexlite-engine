#include "SecondLayer.hpp"

#include <iostream>
#include <memory>

#include <nim/Application/Layer/Event/KeyEvent.hpp>

void SecondLayer::attach()
{
}

void SecondLayer::detach()
{
}

void SecondLayer::update()
{
}

void SecondLayer::render()
{
}

void SecondLayer::event(std::unique_ptr<nim::event::Event>& e)
{
	//std::cout << "second\n";

	if (e->m_Type == nim::event::type::KEY_DOWN)
		std::cout << e->getSelfSubstruct<nim::event::KeyEvent>().m_KeyCode << "\n";
	e->m_Handled = true;
}
