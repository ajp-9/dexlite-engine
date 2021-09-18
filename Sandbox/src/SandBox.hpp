#pragma once

#include <dex/Dexterous.hpp>
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
    
    std::shared_ptr<dex::Material::Default3D> mat = std::make_shared<dex::Material::Default3D>(1, dex::Texture("assets/textures/test.png"));
    //dex::Shader::New3D shader;
    //dex::Component::Model model;
    //dex::Mesh::Default3D mesh;
    //dex::VertexArray varr;
};

DEXTEROUS_DEFINE_MAIN(SandBox);
