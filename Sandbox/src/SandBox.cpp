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
    //m_Player.addComponent<dex::Component::PerspectiveCamera>(true, dex::Camera::Perspective(60, dex::Engine::window.getDimensions(), glm::vec2(.1, 100), glm::vec3(0, 0, -1)));
    
    m_Player.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, 0, -3));
    m_Player.addComponent<dex::Component::Camera>(true);

    //m_Player.getComponent<dex::Component::Camera>().setOrthographic(5, 0.001, 5);
    m_Player.getComponent<dex::Component::Camera>().setPerspective(75, .001, 1000);
    
    m_Player.getComponent<dex::Component::Camera>().updateProjectionMatrix();
    m_Player.getComponent<dex::Component::Camera>().updateViewMatrix();

    shader.bind();

    std::vector<dex::Vertex3D::Color> vertices =
    {
        { glm::vec3(-1, -1, 0), glm::vec4(0, 1, 0, 1)},
        { glm::vec3(0, 1, 0),   glm::vec4(1, 0, 0, 1) },
        { glm::vec3(1, -1, 0),  glm::vec4(0, 0, 1, 1) }
    };

    auto indices = std::vector<uint32>{ 0, 1, 2 };

    varr.bind();

    varr.m_VertexBuffers.setVertexLayout<dex::Vertex3D::Color>(dex::Vertex3D::Color::getTypes());
    varr.m_VertexBuffers.uploadData(vertices);

    varr.m_IndexBuffer.uploadData(indices);
}

void SandBox::Shutdown()
{
    
}

void SandBox::update()
{
    //m_Player.getComponent<dex::Component::Camera>().setOrthographic(10, -5, 5);
    m_Player.getComponent<dex::Component::Camera>().updateProjectionMatrix(); // make into 1
    m_Player.getComponent<dex::Component::Camera>().updateViewMatrix();

    shader.setModelMatrix(m_Entity.getComponent<dex::Component::Transform>());
    shader.setProjectionViewMatrix(m_Player.getComponent<dex::Component::Camera>().getProjectionViewMatrix());
}

void SandBox::render()
{
    static glm::vec3 p = glm::vec3(0);
    p.z += .005;
    //m_Player.getComponent<dex::Component::PerspCamera>().m_Camera.setPosition(p);

    //va.render();
    //m_Scene.render();

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

    static char buf[50];
    ImGui::InputText("Text Input", buf, 50);

    auto& trans = m_Entity.getComponent<dex::Component::Transform>();

    trans.setPosition(glm::vec3(posX, posY, posZ));
    trans.setRotation(glm::vec3(rotX, rotY, rotZ));
    trans.setScale(glm::vec3(scale, scale, scale));
    shader.setModelMatrix(trans);

    ImGui::End();

    //m_Texture.bind();
    varr.bind();
    varr.render();
}
