#include "SandBox.hpp"

#include "TestLayer.hpp"
#include "SecondLayer.hpp"

#include <entt.hpp>
#include <functional>

#include <iostream>

#include <nim/Renderer/OpenGL/VertexArray/Buffers/VertexBuffer.hpp>
#include <nim/Scene/Scene.hpp>
#include <nim/Scene/Entity/Entity.hpp>
#include <nim/Scene/Component/TransformComponent.hpp>
#include "Layers/DebugLayer.hpp"
#include <imgui/imgui.h>

using nim::NimbleEngine;

void printBool(bool i)
{
	std::cout << i << std::endl;
}

void SandBox::Init()
{
	struct component1
	{
		component1(int a)
			: A(a) {}
		int A = 0;
	};


	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<TestLayer>());
	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<SecondLayer>());
	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<DebugLayer>());

	shader.bind();
	shader.setProjectionViewMatrix(pCamera.getProjectionViewMatrix());

	nim::Component::Transform transform;

	shader.setModelMatrix(glm::mat4(1.0f));




	va.m_VertexBuffers.setVertexLayout<VERTEX_LAYOUT>();

	std::vector<Vertex> vertices =
	{	
		{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0, .2, 0)},
	    {glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0, 0, 0)},
	    {glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0, .2, 0)},
		{glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0, 0, 0)}
	};

	va.m_VertexBuffers.uploadData(vertices);

	std::vector<unsigned> indices = { 0, 1, 2, 2, 3, 0 };

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
	static float posZ = -1.0f;

	static const float maxRot = 360;
	static const float maxPos = 20;

	ImGui::SliderFloat("Rotation X", &rotX, 0, maxRot);
	ImGui::SliderFloat("Rotation Y", &rotY, 0, maxRot);
	ImGui::SliderFloat("Rotation Z", &rotZ, 0, maxRot);

	ImGui::NewLine();

	ImGui::SliderFloat("Position X", &posX, -20, maxPos);
	ImGui::SliderFloat("Position Y", &posY, -20, maxPos);
	ImGui::SliderFloat("Position Z", &posZ, -20, maxPos);

	nim::Component::Transform trans;

	trans.setPosition(glm::vec3(posX, posY, posZ));
	trans.setRotation(glm::vec3(rotX, rotY, rotZ));
	shader.setModelMatrix(trans);

	ImGui::End();
}
