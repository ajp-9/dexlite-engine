#pragma once

#include <dex/Dexlite.hpp>
#include <memory>

class SandBox : public dex::Program
{
public:
    virtual void Init() override;
    virtual void Shutdown() override; 

    virtual void update() override;
    virtual void render() override;
private:
    dex::Scene m_Scene;
    dex::Entity m_Player = { &m_Scene };
    dex::Entity m_Entity = { &m_Scene };
    dex::Entity m_Entity2 = { &m_Scene };

    std::shared_ptr<dex::Material::Default3D> mat = std::make_shared<dex::Material::Default3D>(3, dex::Texture("assets/textures/metal.jpg"));
};

DEXLITE_DEFINE_MAIN(SandBox);
