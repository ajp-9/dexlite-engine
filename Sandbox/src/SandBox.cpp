#include "SandBox.hpp"

#include "TestLayer.hpp"
#include "SecondLayer.hpp"

#include <nim/Renderer/Shader/Shader.hpp>

#include <iostream>

#include <nim/Renderer/OpenGL/VertexArray/Buffers/VertexBuffer.hpp>
#include "Layers/DebugLayer.hpp"

using nim::NimbleEngine;

void SandBox::Init()
{
	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<TestLayer>());
	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<SecondLayer>());
	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<DebugLayer>());

	nim::Shader shader("assets/shaders/simple.glsl");

	shader.bind();

	va.m_VertexBuffers.setVertexLayout<VERTEX_TYPES>();

	std::vector<Vertex> vertices =
	{
		{-0.5f, -0.5f, 0.0f, 0.6f},
	    {0.5f, -0.5f, 0.0f, 0.6f },
	    {- 0.0f, 0.5f, 0.0f, 0.0f}
	};

	va.m_VertexBuffers.uploadData(vertices);

	std::vector<unsigned> indices = { 0, 1, 2 };

	va.m_IndexBuffer.uploadData(indices);

	va.unbind();
}

void SandBox::Shutdown()
{
}

void SandBox::update()
{
}

void SandBox::render()
{
	va.bind();
	va.render();
}
