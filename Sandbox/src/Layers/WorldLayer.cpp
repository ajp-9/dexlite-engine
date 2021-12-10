#include "WorldLayer.hpp"

#include <dex/Application/Event/KeyEvent.hpp>

#include <dex/Scene/Component/TransformComponent.hpp>
#include <imgui/imgui.h>
#include <dex/Scene/Component/ModelComponent.hpp>
#include <dex/Util/Logging.hpp>
#include <dex/Renderer/Model/ModelLoader.hpp>

void WorldLayer::Attach()
{
    auto& camera = m_Head.addComponent<dex::Component::Camera>(true);

    //camera.setOrthographic(5, 0.001, 100);
    camera.setPerspective(60, .001, 1000);

    camera.updateProjectionMatrix();
    camera.updateViewMatrix();
    
    dex::Engine::window.setCaptureMouse(true);

    std::vector<dex::Vertex3D::Default> vertices;

    std::vector<uint32> indices;
    
    m_Warlock.addComponent<dex::Component::Model>(dex::ModelLoader::loadGLTF("assets/models/warlock.glb", true));
    m_XYZ.addComponent<dex::Component::Model>(dex::ModelLoader::loadGLTF("assets/models/xyz.glb", true));
    m_XYZ.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, 0, 3.5));
    m_XYZ.getComponent<dex::Component::Transform>().setScale(glm::vec3(.05));

    m_Warlock.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, 0, 10));
    //m_Warlock.getComponent<dex::Component::Transform>().setRotationEuler(glm::vec3(15, 0, 0));

    m_Player.addChild(m_Head);

    //m_Head.addChild(m_XYZ);
    m_Warlock.addChild(m_Player);
}

void WorldLayer::Detach()
{
}

void WorldLayer::update()
{
    m_Scene.update();

    //m_Warlock.getComponent<dex::Component::Transform>().rotateByEulerLocal(glm::vec3(0, glm::radians(.05), glm::radians(.05)));
    //m_Head.getComponent<dex::Component::Transform>().scaleByLocal(glm::vec3(1.001, 1.001, 1.001)); //fucks the camera

    //m_XYZ.getComponent<dex::Component::Transform>().moveBy(glm::vec3(0, 0, .001));



    auto& player_trans = m_Player.getComponent<dex::Component::Transform>();
    auto& head_trans = m_Head.getComponent<dex::Component::Transform>();

    //player_trans.printAsInfo();

    if (Engine::window.input.getKeyState(dex::Event::Key::W))
        player_trans.moveByLocal(glm::vec3(0, 0, 0.01));

    if (Engine::window.input.getKeyState(dex::Event::Key::S))
        player_trans.moveByLocal(glm::vec3(0, 0, -.01));

    if (Engine::window.input.getKeyState(dex::Event::Key::A))
        player_trans.moveByLocal(glm::vec3(-.01, 0, 0));

    if (Engine::window.input.getKeyState(dex::Event::Key::D))
        player_trans.moveByLocal(glm::vec3(.01, 0, 0));

    if (Engine::window.input.getKeyState(dex::Event::Key::Q))
        player_trans.moveByLocal(glm::vec3(0, -.01, 0));

    if (Engine::window.input.getKeyState(dex::Event::Key::E))
        player_trans.moveByLocal(glm::vec3(0, .01, 0));

    const auto& m = Engine::window.input.getMousePosChange() * .002;

    player_trans.rotateByEuler((glm::vec3(0, m.x, 0)));

    float max_degrees = 90;
    
    if (head_trans.getRotationDegrees().x -m.y <= max_degrees && head_trans.getRotationDegrees().x -m.y >= -max_degrees)
        head_trans.rotateByEulerLocal((glm::vec3(-m.y, 0, 0)));
    else if (head_trans.getRotationDegrees().x > max_degrees)
        head_trans.setRotationEuler(glm::vec3(glm::radians(max_degrees), 0, 0));
    else if (head_trans.getRotationDegrees().x < -max_degrees)
        head_trans.setRotationEuler(glm::vec3(glm::radians(-max_degrees), 0, 0));
    

    if (Engine::window.input.getKeyState(dex::Event::Key::KB_1))
        dex::Engine::window.setFullscreen();

    if (Engine::window.input.getKeyState(dex::Event::Key::KB_2))
        dex::Engine::window.setWindowed();

    if (Engine::window.input.getKeyState(dex::Event::Key::O))
        dex::Engine::window.setCaptureMouse(true);
    if (Engine::window.input.getKeyState(dex::Event::Key::P))
        dex::Engine::window.setCaptureMouse(false);

    Engine::window.input.stopEvents();
}

void WorldLayer::render()
{
    /*
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
    //trans.m_Rotation = glm::quat(glm::radians(glm::vec3(rotX, rotY, rotZ)));
    trans.setScale(glm::vec3(scale, scale, scale));
    */
    Engine::renderer.renderScene(m_Scene);

    //ImGui::End();
}
