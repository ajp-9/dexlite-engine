#include "SandBox.hpp"

#include "TestLayer.hpp"
#include "SecondLayer.hpp"


#include <iostream>

#include <nim/Renderer/OpenGL/VertexArray/Buffers/VertexBuffer.hpp>
#include "Layers/DebugLayer.hpp"
#include <imgui/imgui.h>


using nim::NimbleEngine;

void SandBox::Init()
{
	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<TestLayer>());
	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<SecondLayer>());
	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<DebugLayer>());


	shader.bind();
	shader.setMat4Uniform("u_ProjectionViewMatrix", oCamera.getProjectionViewMatrix());

	va.m_VertexBuffers.setVertexLayout<VERTEX_LAYOUT>();

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

	ImGui::Begin("Test Window");

	static float posX = 0.0f;
	ImGui::SliderFloat("posx", &posX, -500.75, 500.75);
	oCamera.setRotation(glm::vec3(posX, 0, 0));
	shader.setMat4Uniform("u_ProjectionViewMatrix", oCamera.getProjectionViewMatrix());

	ImGui::End();
}
