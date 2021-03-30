#pragma once

#include <nim/Nimble.hpp>
#include <nim/Renderer/OpenGL/VertexArray/VertexArray.hpp>
#include <nim/Renderer/Camera/OrthographicCamera.hpp>
#include <nim/Renderer/Camera/PerspectiveCamera.hpp>
#include <nim/Renderer/Model/Material/Shader/Shader.hpp>

#include "TestLayer.hpp"

#define VERTEX_LAYOUT glm::vec3, glm::vec3
struct Vertex
{
	Vertex() : pos(0), color(0) {}
	Vertex(glm::vec3 pos, glm::vec3 color)
		: pos(pos), color(color) {}
	glm::vec3 pos;
	glm::vec3 color;
};

class SandBox : public nim::Program
{
public:
	virtual void Init() override;
	virtual void Shutdown() override; 

	virtual void update() override;
	virtual void render() override;

private:
	nim::GL::VertexArray<Vertex> va;
	//nim::OrthographicCamera oCamera = nim::OrthographicCamera(glm::vec4(-0.75f, 0.75f, -0.75f, 0.75f), glm::vec3(0), glm::vec3(0));
	nim::PerspectiveCamera pCamera = nim::PerspectiveCamera(80, nim::NimbleEngine::m_Window.getDimensions(), glm::vec2(.1, 100));
	nim::Shader shader = nim::Shader("assets/shaders/simple.glsl");
};

NIMBLE_DEFINE_MAIN(SandBox);
