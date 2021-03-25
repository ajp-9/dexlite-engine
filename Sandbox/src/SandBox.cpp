#include "SandBox.hpp"

#include "TestLayer.hpp"
#include "SecondLayer.hpp"
#include <iostream>
#include <nim/Scene/Scene.hpp>
#include <nim/Scene/Component/RenderableComponent.h>
#include <nim/Scene/Entity/Entity.hpp>

#include <nim/Renderer/Shader/Shader.hpp>

#include <glad/glad.h>

using nim::NimbleEngine;

void SandBox::Init()
{
	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<TestLayer>());
	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<SecondLayer>());

	nim::Shader shader("assets/shaders/simple.glsl");

	shader.bind();

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.0f,  0.5f, 0.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

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
