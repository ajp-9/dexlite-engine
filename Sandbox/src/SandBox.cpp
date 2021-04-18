#include "SandBox.hpp"

#include "Layers/WorldLayer.hpp"

#include <entt.hpp>

#include <iostream>

#include <dex/Renderer/VertexArray/Buffers/VertexBuffer.hpp>
#include <dex/Scene/Component/TransformComponent.hpp>
#include "Layers/DebugLayer.hpp"
#include <imgui/imgui.h>
#include <dex/Scene/Component/ModelComponent.hpp>
#include <dex/Scene/Component/Camera/PerspCamera.hpp>
#include <dex/Renderer/Texture/Texture.hpp>

#include <assimp/Importer.hpp>

using dex::Engine;

void SandBox::Init()
{
	Assimp::Importer impoter;
	impoter.ReadFile("eewwe", 0);
	Engine::m_LayerManager.pushLayer(std::make_shared<WorldLayer>());
	Engine::m_LayerManager.pushLayer(std::make_shared<DebugLayer>());

	shader->bind();
	shader->setInt("u_TextureSampler", 0);
	dex::ShaderManager::addShader(shader);
	//shader->setProjectionViewMatrix(pCamera.getProjectionViewMatrix());
	m_Player = m_Scene.createEntity();
	m_Player.addComponent<dex::Component::PerspCamera>(true, dex::PerspectiveCamera(60, dex::Engine::m_Window.getDimensions(), glm::vec2(.1, 100), glm::vec3(0, 0, -1)));

	m_Scene.findSetMainCamera();


	std::vector<dex::Vertex_TextureNormal3D> vertices =
	{
		{glm::vec3( 0.5f,  0.5f, 0.0f),   glm::vec3(1.0f, 0.0f, 0.0f),   glm::vec2(1.0f, 1.0f)}, // top right
		{glm::vec3( 0.5f, -0.5f, 0.0f),   glm::vec3(0.0f, 1.0f, 0.0f),   glm::vec2(1.0f, 0.0f)}, // bottom right
		{glm::vec3(-0.5f, -0.5f, 0.0f),   glm::vec3(0.0f, 0.0f, 1.0f),   glm::vec2(0.0f, 0.0f)}, // bottom left
		{glm::vec3(-0.5f,  0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 0.0f),   glm::vec2(0.0f, 1.0f)}  // top left 
	};

	std::vector<unsigned> indices = { 0, 1, 3, 1, 2, 3 };
	//std::unique_ptr<dex::Mesh> m = std::make_unique<dex::Mesh>(vertices, indices);

	m_Entity = m_Scene.createEntity();

	m_Entity.addComponent<dex::Component::Model>(std::make_unique<dex::Mesh::Mesh_TextureNormal3D>(vertices, indices), std::make_unique<dex::Material::Material>(shader));
	m_Entity.addComponent<dex::Component::Transform>();
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
	m_Player.getComponent<dex::Component::PerspCamera>().m_Camera.setPosition(p);*/

	//va.render();
	m_Scene.render();

	ImGui::Begin("Test Window");

	static float rotX = 0.0f;
	static float rotY = 0.0f;
	static float rotZ = 0.0f;

	static float posX = 0.0f;
	static float posY = 0.0f;
	static float posZ = 0.0f;

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

	auto& trans = m_Entity.getComponent<dex::Component::Transform>();

	trans.setPosition(glm::vec3(posX, posY, posZ));
	trans.setRotation(glm::vec3(rotX, rotY, rotZ));
	//shader->setModelMatrix(trans);

	ImGui::End();
	m_Texture.bind();

}
