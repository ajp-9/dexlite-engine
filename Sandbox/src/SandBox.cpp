#include "SandBox.hpp"

#include "Layers/WorldLayer.hpp"

#include <entt.hpp>

#include <iostream>

#include <dex/Scene/Component/TransformComponent.hpp>
#include "Layers/DebugLayer.hpp"
#include <imgui/imgui.h>
#include <dex/Scene/Component/ModelComponent.hpp>
#include <dex/Util/Logging.hpp>
#include <dex/Renderer/Model/ModelLoader.hpp>

using dex::Engine;

void SandBox::Init()
{
    Engine::layerManager.pushLayer(std::make_shared<WorldLayer>());
    Engine::layerManager.pushLayer(std::make_shared<DebugLayer>());

    auto& camera = m_Player.addComponent<dex::Component::Camera>(true);

    camera.setOrthographic(5, 0.001, 100);
    //camera.setPerspective(60, .001, 1000);

    camera.updateProjectionMatrix();
    camera.updateViewMatrix();

    //dex::Engine::window.setCaptureMouse(true);

    std::vector<dex::Vertex3D::Default> vertices;

    std::vector<uint32> indices;

    m_Entity.addComponent<dex::Component::Model>(dex::ModelLoader::loadGLTF("assets/models/warlock-turned.glb", true));
    //m_Entity2.addComponent<dex::Component::Model>(dex::ModelLoader::loadGLTF("assets/models/xyz.glb", true));
    m_Entity2.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, 0, 3.5));
    m_Entity2.getComponent<dex::Component::Transform>().setScale(glm::vec3(.05));
}

void SandBox::Shutdown()
{

}

void SandBox::update()
{
    auto& player_trans = m_Player.getComponent<dex::Component::Camera>();

    auto& m = Engine::window.input.getMousePosChange();

    auto& ent = m_Entity.getComponent<dex::Component::Transform>();

    //ent.rotateByDegrees()

    player_trans.m_Rot += glm::vec3(.001) * glm::vec3(m.y, -m.x, 0);

    player_trans.updateViewMatrix();

    if (Engine::window.input.getKeyState(dex::Event::Key::W))
    {
        player_trans.m_Rot += glm::vec3(0.01, 0, 0);

        player_trans.updateViewMatrix();
    }

    if (Engine::window.input.getKeyState(dex::Event::Key::S))
    {
        player_trans.m_Rot += glm::vec3(-0.01, 0, 0);

        player_trans.updateViewMatrix();
    }

    if (Engine::window.input.getKeyState(dex::Event::Key::A))
    {
        player_trans.m_Rot += glm::vec3(0, 0.01, 0);

        player_trans.updateViewMatrix();
    }

    if (Engine::window.input.getKeyState(dex::Event::Key::D))
    {
        player_trans.m_Rot += glm::vec3(0, -0.01, 0);

        player_trans.updateViewMatrix();
    }


    /*glm::vec3& rot_e = glm::eulerAngles(player_trans.m_Rotation);
    glm::quat QuatAroundX = glm::angleAxis(rot_e.x, glm::vec3(1.0, 0.0, 0.0));
    glm::quat QuatAroundY = glm::angleAxis(rot_e.y, glm::vec3(0.0, 1.0, 0.0));
    glm::quat QuatAroundZ = glm::angleAxis(rot_e.z, glm::vec3(0.0, 0.0, 1.0));
    glm::quat finalOrientation = QuatAroundX * QuatAroundY * QuatAroundZ;
    player_trans.m_Rotation = finalOrientation;*/

    if (Engine::window.input.getKeyState(dex::Event::Key::KB_1))
        dex::Engine::window.setFullscreen();

    if (Engine::window.input.getKeyState(dex::Event::Key::KB_2))
        dex::Engine::window.setWindowed();

    if (Engine::window.input.getKeyState(dex::Event::Key::O))
        dex::Engine::window.setCaptureMouse(true);
    if (Engine::window.input.getKeyState(dex::Event::Key::P))
        dex::Engine::window.setCaptureMouse(false);
}

void SandBox::render()
{
    //auto& model = m_Player.getComponent<dex::Component::Model>();

    //model.m_Material->m_Shader->bind();

    ImGui::Begin("Test Window");

    static float rotX = 0.0f;
    static float rotY = 0.0f;
    static float rotZ = 0.0f;

    static float old_rotX = 0.0f;
    static float old_rotY = 0.0f;
    static float old_rotZ = 0.0f;

    static float posX = 0.0f;
    static float posY = 0.0f;
    static float posZ = 2.0f;

    static float scale = 0.5f;

    static const float maxRot = 720;
    static const float maxPos = 5;

    ImGui::SliderFloat("Rotation X", &rotX, 0, maxRot);
    ImGui::SliderFloat("Rotation Y", &rotY, 0, maxRot);
    ImGui::SliderFloat("Rotation Z", &rotZ, 0, maxRot);
     
    ImGui::NewLine();

    ImGui::SliderFloat("Position X", &posX, -maxPos, maxPos);
    ImGui::SliderFloat("Position Y", &posY, -maxPos, maxPos);
    ImGui::SliderFloat("Position Z", &posZ, -maxPos, maxPos);

    ImGui::NewLine();

    ImGui::SliderFloat("Scale X", &scale, 0.001, 1);

    //static char buf[50];
    //ImGui::InputText("Text Input", buf, 50);

    auto& trans = m_Entity.getComponent<dex::Component::Transform>();

    trans.setPosition(glm::vec3(posX, posY, posZ));
    trans.m_Rotation = glm::quat(glm::radians(glm::vec3(rotX, rotY, rotZ)));
    trans.setScale(glm::vec3(scale, scale, scale));

    Engine::renderer.renderScene(m_Scene);

    ImGui::End();
}
