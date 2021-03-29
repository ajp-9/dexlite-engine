#include "SandBox.hpp"

#include "TestLayer.hpp"
#include "SecondLayer.hpp"

#include <entt.hpp>

#include <iostream>

#include <nim/Renderer/OpenGL/VertexArray/Buffers/VertexBuffer.hpp>
#include "Layers/DebugLayer.hpp"
#include <imgui/imgui.h>

using nim::NimbleEngine;

void SandBox::Init()
{
	struct component1
	{
		component1(int a)
			: A(a) {}
		int A = 0;
	};

	entt::registry mRegistry;
	entt::entity entity = mRegistry.create();

	mRegistry.emplace<component1>(entity, 2);





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

	static float rotX = 0.0f;
	static float rotY = 0.0f;
	static float rotZ = 0.0f;

	static float posX = 0.0f;
	static float posY = 0.0f;
	static float posZ = 0.0f;

	static const float maxRot = 360;
	static const float maxPos = 2;

	ImGui::SliderFloat("Rotation X", &rotX, 0, maxRot);
	ImGui::SliderFloat("Rotation Y", &rotY, 0, maxRot);
	ImGui::SliderFloat("Rotation Z", &rotZ, 0, maxRot);

	ImGui::NewLine();

	ImGui::SliderFloat("Position X", &posX, -2, maxPos);
	ImGui::SliderFloat("Position Y", &posY, -2, maxPos);
	ImGui::SliderFloat("Position Z", &posZ, -2, maxPos);

	oCamera.setPosition(glm::vec3(posX, posY, posZ));
	oCamera.setRotation(glm::vec3(rotX, rotY, rotZ));
	shader.setMat4Uniform("u_ProjectionViewMatrix", oCamera.getProjectionViewMatrix());

	ImGui::End();
}
