#pragma once

#include <zim/Nimble.hpp>
#include <zim/Renderer/Camera/OrthographicCamera.hpp>
#include <zim/Renderer/Camera/PerspectiveCamera.hpp>
#include <zim/Renderer/Shader/Shader.hpp>
#include <zim/Scene/Scene.hpp>
#include <zim/Scene/Entity/Entity.hpp>
#include <zim/Renderer/Mesh/Vertex.hpp>

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
	zim::PerspectiveCamera pCamera = zim::PerspectiveCamera(60, zim::ZimbleEngine::m_Window.getDimensions(), glm::vec2(.1, 100));
	std::shared_ptr<zim::Shader> shader = std::make_shared<zim::Shader>("assets/shaders/simple.glsl");
	zim::Scene m_Scene;
	zim::Entity m_Entity;
};

NIMBLE_DEFINE_MAIN(SandBox);
