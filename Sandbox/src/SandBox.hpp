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
    dex::Entity m_Player;
    dex::Entity m_Entity;
    
    std::shared_ptr<dex::Material::Default3D> mat = std::make_shared<dex::Material::Default3D>(3, dex::Texture("assets/textures/metal.jpg"));
    //dex::Shader::New3D shader;
    //dex::Component::Model model;
    //dex::Mesh::Default3D mesh;
    //dex::VertexArray varr;
};

DEXTEROUS_DEFINE_MAIN(SandBox);
