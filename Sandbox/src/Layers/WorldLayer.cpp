#include "WorldLayer.hpp"

#include <dex/Application/Event/KeyEvent.hpp>

void WorldLayer::Attach()
{
}

void WorldLayer::Detach()
{
}

void WorldLayer::update()
{
    if (Engine::window.input.isKeyPressed(dex::Event::Key::LEFT_CONTROL))
        std::cout << "Clicked" << "\n";
}

void WorldLayer::render()
{
}

void WorldLayer::event(dex::Event::Base& e)
{
    //if (e.m_Type == dex::Event::Type::KEY_DOWN)
    //    std::cout << (int32_t)e.getDerivedSelf<dex::Event::KeyEvent>().m_KeyCode << "\n";

    //std::cout << (int)e.m_Type << "\n";
}
