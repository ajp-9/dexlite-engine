#pragma once

#include <nim/Nimble.hpp>
#include <nim/Renderer/Camera/OrthographicCamera.hpp>
#include <nim/Renderer/Camera/PerspectiveCamera.hpp>
#include <nim/Renderer/Shader/Shader.hpp>
#include <nim/Scene/Scene.hpp>
#include <nim/Scene/Entity/Entity.hpp>
#include <nim/Renderer/Mesh/Vertex.hpp>

#include "TestLayer.hpp"

class SandBox : public nim::Program
{
public:
	virtual void Init() override;
	virtual void Shutdown() override; 

	virtual void update() override;
	virtual void render() override;
private:
	//nim::OrthographicCamera oCamera = nim::OrthographicCamera(glm::vec4(-0.75f, 0.75f, -0.75f, 0.75f), glm::vec3(0), glm::vec3(0));
	nim::PerspectiveCamera pCamera = nim::PerspectiveCamera(60, nim::NimbleEngine::m_Window.getDimensions(), glm::vec2(.1, 100));
	std::shared_ptr<nim::Shader> shader = std::make_shared<nim::Shader>("assets/shaders/simple.glsl");
	nim::Scene m_Scene;
	nim::Entity m_Entity;
};

NIMBLE_DEFINE_MAIN(SandBox);
