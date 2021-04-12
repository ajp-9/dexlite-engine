#pragma once

#include <zim/Zimble.hpp>
#include <zim/Renderer/Shader/Shader3D.hpp>
#include "TestLayer.hpp"

class SandBox : public zim::Program
{
public:
	virtual void Init() override;
	virtual void Shutdown() override; 

	virtual void update() override;
	virtual void render() override;
private:
	//zim::OrthographicCamera oCamera = zim::OrthographicCamera(glm::vec4(-0.75f, 0.75f, -0.75f, 0.75f), glm::vec3(0), glm::vec3(0));
	//zim::PerspectiveCamera pCamera = zim::PerspectiveCamera(60, zim::ZimbleEngine::m_Window.getDimensions(), glm::vec2(.1, 100), glm::vec3(0, 0, -1));
	std::shared_ptr<zim::Shader> shader = std::make_shared<zim::Shader3D>("assets/shaders/simple.glsl", "Shader3D");
	zim::Scene m_Scene;
	zim::Entity m_Entity;
};

ZIMBLE_DEFINE_MAIN(SandBox);
