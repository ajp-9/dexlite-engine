#pragma once

#include <dex/Core/Engine.hpp>
#include <dex/Dexlite.hpp>

class WorldLayer : public dex::Layer::Base
{
public:
    virtual void Attach() override;
    virtual void Detach() override;

    virtual void update() override;
    virtual void render() override;
private:
    dex::Scene m_Scene;

    dex::Entity m_Player = { &m_Scene, "Player"};
    dex::Entity m_Head = { &m_Scene, "Head"};

    dex::Entity m_XYZ = { &m_Scene, "XYZ"};
    dex::Entity m_Warlock = { &m_Scene, "Warlock"};
    dex::Entity m_LightSphere = { &m_Scene, "Light Sphere" };
    dex::Entity m_Triangle = { &m_Scene, "Triangle" };
};
