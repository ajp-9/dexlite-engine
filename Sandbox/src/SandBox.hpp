#pragma once

#include <stb_image.h>
#include <dex/Dexterous.hpp>
#include <dex/Renderer/Shader/3D/ShaderInterface3D.hpp>
#include <dex/Renderer/Shader/3D/ShaderColor3D.hpp>
#include <dex/Renderer/Shader/3D/ShaderTexture3D.hpp>

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
};

DEXTEROUS_DEFINE_MAIN(SandBox);
