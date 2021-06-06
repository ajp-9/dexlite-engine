#include "SandBox.hpp"

#include "Layers/WorldLayer.hpp"

#include <entt.hpp>

#include <iostream>

#include <dex/Scene/Component/TransformComponent.hpp>
#include "Layers/DebugLayer.hpp"
#include <imgui/imgui.h>
#include <dex/Scene/Component/ModelComponent.hpp>

using dex::Engine;

void SandBox::Init()
{
	Engine::s_LayerManager.pushLayer(std::make_shared<WorldLayer>());
	Engine::s_LayerManager.pushLayer(std::make_shared<DebugLayer>());

	/*
	//shader->setProjectionViewMatrix(pCamera.getProjectionViewMatrix());
	m_Player = m_Scene.createEntity();
	m_Player.addComponent<dex::Component::PerspectiveCamera>(true, dex::Camera::Perspective(60, dex::Engine::m_Window.getDimensions(), glm::vec2(.1, 100), glm::vec3(0, 0, -1)));

	m_Scene.findSetMainCamera();

	/*std::vector<dex::Vertex3D::TextureNormal> vertices =
	{
		{glm::vec3(0.5f,  0.5f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)}, // top right
		{glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)}, // bottom right
		{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)}, // bottom left
		{glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}  // top left 
	};

	std::vector<unsigned> indices = { 0, 1, 3, 1, 2, 3 };
	//std::unique_ptr<dex::Mesh> m = std::make_unique<dex::Mesh>(vertices, indices);/

	m_Entity = m_Scene.createEntity();

	m_Entity.addComponent<dex::Component::Model>(dex::Model("assets/models/box.fbx", std::make_unique<dex::Material::Base>(shader)));
	m_Entity.addComponent<dex::Component::Transform>();
	
	dex::Shader::UniformBufferObject proj = { "ubo_ProjectionViewMatrix" };
	proj.bindShader(shader);

	proj.setup();

	__declspec(align(16)) struct Data
	{
		Data(float v) : values(v) {}

		int b = 3;
		__declspec(align(16)) glm::vec3 w = glm::vec3(0);
		__declspec(align(16)) glm::mat4 m = glm::mat4(0);
		__declspec(align(16)) glm::vec2 w1 = glm::vec2(0);
		int what = 0;
		__declspec(align(16)) glm::vec3 w2 = glm::vec3(0);
		float values = 1;
	};

	Data dat[2] = { Data(0), Data(1) };

	dat[0].w = glm::vec3(0, 3, 1);

	proj.uploadData(&dat);*/

	/*std::vector<dex::Vertex3D::Default> vertices = {dex::Vertex3D::Default(), dex::Vertex3D::Default()};
	std::vector<unsigned> indices = { 0, 1, 3, 1, 2, 3 };
	dex::Material::Default3D material = { dex::Renderer::s_ShaderManager.getShaderDerived<dex::Shader::Default3D>("Default3D") };

	std::unique_ptr<dex::Mesh::Base> m = std::make_unique<dex::Mesh::Default3D>(vertices, indices, material);
	m->getDerivedSelf<dex::Mesh::TextureNormal3D>();

	std::cout << material.m_Shader->getName() << "\n";*/

	//std::unique_ptr<dex::Mesh::Base> def = std::make_unique<dex::Mesh::Default3D>(vertices, indices, materials);
	//std::cout << (uint32_t)def->m_Type << "\n";
}

void SandBox::Shutdown()
{

}

void SandBox::update()
{
}

void SandBox::render()
{
	/*static glm::vec3 p = glm::vec3(0);
	p.z += .005;
	m_Player.getComponent<dex::Component::PerspCamera>().m_Camera.setPosition(p);

	//va.render();
	m_Scene.render();

	ImGui::Begin("Test Window");

	static float rotX = 45.0f;
	static float rotY = 35.0f;
	static float rotZ = 90.0f;

	static float posX = 0.0f;
	static float posY = 0.0f;
	static float posZ = 5.0f;

	static float scale = 1.0f;

	static const float maxRot = 360;
	static const float maxPos = 20;

	ImGui::SliderFloat("Rotation X", &rotX, 0, maxRot);
	ImGui::SliderFloat("Rotation Y", &rotY, 0, maxRot);
	ImGui::SliderFloat("Rotation Z", &rotZ, 0, maxRot);

	ImGui::NewLine();

	ImGui::SliderFloat("Position X", &posX, -20, maxPos);
	ImGui::SliderFloat("Position Y", &posY, -20, maxPos);
	ImGui::SliderFloat("Position Z", &posZ, -20, maxPos);

	ImGui::NewLine();

	ImGui::SliderFloat("Scale X", &scale, 0.1, 1);

	static char buf[50];
	ImGui::InputText("Text Input", buf, 50);

	auto& trans = m_Entity.getComponent<dex::Component::Transform>();

	trans.setPosition(glm::vec3(posX, posY, posZ));
	trans.setRotation(glm::vec3(rotX, rotY, rotZ));
	trans.setScale(glm::vec3(scale, scale, scale));
	//shader->setModelMatrix(trans);

	ImGui::End();
	m_Texture.bind();*/

}
