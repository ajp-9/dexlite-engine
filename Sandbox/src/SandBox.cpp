#include "SandBox.hpp"

#include "TestLayer.hpp"
#include "SecondLayer.hpp"

#include <entt.hpp>

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <nim/Renderer/VertexArray/Buffers/VertexBuffer.hpp>
#include <nim/Scene/Component/TransformComponent.hpp>
#include "Layers/DebugLayer.hpp"
#include <imgui/imgui.h>
#include <nim/Scene/Component/ModelComponent.hpp>

using nim::NimbleEngine;

void SandBox::Init()
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("", aiProcess_Triangulate | aiProcess_FlipUVs);


	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<TestLayer>());
	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<SecondLayer>());
	NimbleEngine::m_LayerManager.pushLayer(std::make_shared<DebugLayer>());

	shader->bind();
	shader->setProjectionViewMatrix(pCamera.getProjectionViewMatrix());

	std::vector<nim::Vertex> vertices =
	{
		{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0, .3, 0), glm::vec2(0, 0),},
		{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0, 0, 0) , glm::vec2(0, 0),},
		{glm::vec3(0.5f,  0.5f, 0.0f), glm::vec3(0, .3, 0), glm::vec2(0, 0),},
		{glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0, 0, 0) , glm::vec2(0, 0)}
	};

	std::vector<unsigned> indices = { 0, 1, 2, 2, 3, 0 };

	m_Entity = m_Scene.createEntity();

	m_Entity.addComponent<nim::Component::Model>(nim::Mesh(vertices, indices), shader);
	m_Entity.addComponent<nim::Component::Transform>();
}

void SandBox::Shutdown()
{

}

void SandBox::update()
{
}

void SandBox::render()
{
	//va.render();
	m_Scene.render();

	ImGui::Begin("Test Window");

	static float rotX = 0.0f;
	static float rotY = 0.0f;
	static float rotZ = 0.0f;

	static float posX = 0.0f;
	static float posY = 0.0f;
	static float posZ = 1.0f;

	static const float maxRot = 360;
	static const float maxPos = 20;

	ImGui::SliderFloat("Rotation X", &rotX, 0, maxRot);
	ImGui::SliderFloat("Rotation Y", &rotY, 0, maxRot);
	ImGui::SliderFloat("Rotation Z", &rotZ, 0, maxRot);

	ImGui::NewLine();

	ImGui::SliderFloat("Position X", &posX, -20, maxPos);
	ImGui::SliderFloat("Position Y", &posY, -20, maxPos);
	ImGui::SliderFloat("Position Z", &posZ, -20, maxPos);

	static char buf[50];
	ImGui::InputText("Text Input", buf, 50);

	nim::Component::Transform trans;

	trans.setPosition(glm::vec3(posX, posY, posZ));
	trans.setRotation(glm::vec3(rotX, rotY, rotZ));
	shader->setModelMatrix(trans);

	ImGui::End();
}
