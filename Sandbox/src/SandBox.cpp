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
    Engine::layerManager.pushLayer(std::make_shared<WorldLayer>());
    Engine::layerManager.pushLayer(std::make_shared<DebugLayer>());

    m_Player = m_Scene.createEntity();
    m_Entity = m_Scene.createEntity();

    auto& camera = m_Player.addComponent<dex::Component::Camera>(true);
    
    //camera.setOrthographic(5, 0.001, 5);
    camera.setPerspective(60, .001, 1000);

    camera.updateProjectionMatrix();
    camera.updateViewMatrix();

    std::vector<dex::Vertex3D::Default> vertices =
    {
        dex::Vertex3D::Default(glm::vec3(-1, -1, 0), glm::vec3(0, 0, 0), glm::vec4(0, 1, 0, 1)),
        dex::Vertex3D::Default(glm::vec3(0, 1, 0),   glm::vec3(0, 0, 0), glm::vec4(1, 0, 0, 1)),
        dex::Vertex3D::Default(glm::vec3(1, -1, 0),  glm::vec3(0, 0, 0), glm::vec4(0, 0, 1, 1))
    };

    auto indices = std::vector<uint32>{ 0, 1, 2 };

    m_Entity.addComponent<dex::Component::Model>(dex::Mesh::Default3D(vertices, indices), mat);
    auto& model = m_Entity.getComponent<dex::Component::Model>();

    //model.m_Material->m_Shader->bind();
}

void SandBox::Shutdown()
{

}

void SandBox::update()
{
}

void SandBox::render()
{
    //auto& model = m_Player.getComponent<dex::Component::Model>();

    //model.m_Material->m_Shader->bind();

    ImGui::Begin("Test Window");

    static float rotX = 0.0f;
    static float rotY = 0.0f;
    static float rotZ = 0.0f;

    static float posX = 0.0f;
    static float posY = 0.0f;
    static float posZ = 2.5f;

    static float scale = 1.0f;

    static const float maxRot = 360;
    static const float maxPos = 5;

    ImGui::SliderFloat("Rotation X", &rotX, 0, maxRot);
    ImGui::SliderFloat("Rotation Y", &rotY, 0, maxRot);
    ImGui::SliderFloat("Rotation Z", &rotZ, 0, maxRot);
     
    ImGui::NewLine();

    ImGui::SliderFloat("Position X", &posX, -maxPos, maxPos);
    ImGui::SliderFloat("Position Y", &posY, -maxPos, maxPos);
    ImGui::SliderFloat("Position Z", &posZ, -maxPos, maxPos);

    ImGui::NewLine();

    ImGui::SliderFloat("Scale X", &scale, 0.1, 1.5);

    //static char buf[50];
    //ImGui::InputText("Text Input", buf, 50);

    auto& trans = m_Entity.getComponent<dex::Component::Transform>();

    trans.setPosition(glm::vec3(posX, posY, posZ));
    trans.setRotation(glm::vec3(rotX, rotY, rotZ));
    trans.setScale(glm::vec3(scale, scale, scale));
    //m_Entity.getComponent<dex::Component::Model>().m_Material->m_Shader->setModelMatrix(trans);

    //model.m_Mesh.render();

    Engine::renderer.renderScene(m_Scene);

    ImGui::End();

    //m_Texture.bind();
}
