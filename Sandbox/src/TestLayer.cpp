#include "TestLayer.hpp"

#include <iostream>
#include <memory>

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
	std::cout << e->m_Type << "\n";
}
