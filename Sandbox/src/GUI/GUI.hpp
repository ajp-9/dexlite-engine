#pragma once

#include "../World/World.hpp"

class GUI
{
public:
    GUI(World* world)
        : m_WorldHandle(world)
    {}

    void render();
private:
    World* m_WorldHandle;
};
