#include "SandBox.hpp"

#include "TestLayer.hpp"
#include "SecondLayer.hpp"

#include <nim/Renderer/Shader/Shader.hpp>
#include <glm/vec3.hpp>

#include <iostream>

#include <nim/Renderer/OpenGL/Buffers/VertexBuffer.hpp>

#include <glad/glad.h>

using nim::NimbleEngine;

void SandBox::Init()
{
	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<TestLayer>());
	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<SecondLayer>());

	nim::Shader shader("assets/shaders/simple.glsl");

	shader.bind();

	struct Vertex
	{
		Vertex() : pos(0), color(0) {}
		Vertex(float x, float y, float z, float color)
			: pos(glm::vec3(x, y, z)), color(color) {}
		glm::vec3 pos;
		float color;
	};

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	nim::gl::VertexBuffer<Vertex> vb;
	vb.bind();
	
	vb.setVertexLayout<glm::vec3, float>();

	std::vector<Vertex> vertices =
	{
		{-0.5f, -0.5f, 0.0f, 1.f},
	    {0.5f, -0.5f, 0.0f, 0.0f },
	    {- 0.0f, 0.5f, 0.0f, .5f}
	};


	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	vb.uploadData(vertices);

	uint indices[] = { 0, 1, 2 };

	glGenBuffers(1, &m_IBO);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void SandBox::Shutdown()
{
}

void SandBox::update()
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}

void SandBox::render()
{
}
