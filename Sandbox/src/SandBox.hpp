#pragma once

#include <nim/Nimble.hpp>
#include <nim/Renderer/OpenGL/VertexArray/VertexArray.hpp>

#include "TestLayer.hpp"

#define VERTEX_TYPES glm::vec3, float
struct Vertex
{
	Vertex() : pos(0), color(0) {}
	Vertex(float x, float y, float z, float color)
		: pos(glm::vec3(x, y, z)), color(color) {}
	glm::vec3 pos;
	float color;
};

class SandBox : public nim::Program
{
public:
	virtual void Init() override;
	virtual void Shutdown() override; 

	virtual void update() override;
	virtual void render() override;

private:
	uint m_VAO, m_VBO, m_IBO;
	nim::gl::VertexArray<Vertex> va;
};

NIMBLE_DEFINE_MAIN(SandBox);
