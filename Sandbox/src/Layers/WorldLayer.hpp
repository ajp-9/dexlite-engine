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
    dex::Entity m_Player = m_Scene.createEntity();
    dex::Entity m_Entity = m_Scene.createEntity();
    dex::Entity m_Entity2 = m_Scene.createEntity();
};
