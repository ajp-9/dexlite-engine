#pragma once

#include <stb_image.h>
#include <dex/Dexterous.hpp>
#include <dex/Renderer/Shader/3D/Shader3D.hpp>
#include <dex/Renderer/Shader/3D/ShaderAlbedo3D.hpp>
#include <dex/Renderer/Shader/3D/ShaderTexture3D.hpp>

class SandBox : public dex::Program
{
public:
	virtual void Init() override;
	virtual void Shutdown() override; 

	virtual void update() override;
	virtual void render() override;
private:
	//dex::OrthographicCamera oCamera = dex::OrthographicCamera(glm::vec4(-0.75f, 0.75f, -0.75f, 0.75f), glm::vec3(0), glm::vec3(0));
	//dex::PerspectiveCamera pCamera = dex::PerspectiveCamera(60, dex::Engine::m_Window.getDimensions(), glm::vec2(.1, 100), glm::vec3(0, 0, -1));
	std::shared_ptr<dex::Shader::ShaderTexture3D> shader = std::make_shared<dex::Shader::ShaderTexture3D>();
	dex::Texture m_Texture = dex::Texture("assets/textures/test.png");
	dex::Scene m_Scene;
	dex::Entity m_Entity;
	dex::Entity m_Player;
};

ZIMBLE_DEFINE_MAIN(SandBox);
