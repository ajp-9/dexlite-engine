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
    dex::Entity m_Entity;
    dex::Entity m_Player;
    
    dex::Shader::New3D shader;
    dex::VertexArray varr;
};

DEXTEROUS_DEFINE_MAIN(SandBox);
