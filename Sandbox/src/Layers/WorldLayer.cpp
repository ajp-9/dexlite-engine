#include "WorldLayer.hpp"

#include <dex/Application/Event/KeyEvent.hpp>

#include <dex/Scene/Component/TransformComponent.hpp>
#include <imgui/imgui.h>
#include <dex/Scene/Component/Model/ModelComponent.hpp>
#include <dex/Util/Logging.hpp>
#include <dex/Scene/Component/LightComponents.hpp>

#include <filesystem>

void WorldLayer::Attach()
{
    auto& camera = m_Head.addComponent<dex::Component::Camera>(true);

    //camera.setOrthographic(5, 0.001, 100);
    camera.setPerspective(65, 0.01, 1000);
    
    dex::Engine::Window.setCaptureMouse(true);
    
    m_Warlock.addComponent<dex::Component::Model>("assets/models/warlock.glb", true);
    m_Warlock.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, 0, 10));
    //m_Warlock.getComponent<dex::Component::Transform>().setRotationEuler(glm::vec3(15, 0, 0));
    
    m_XYZ.addComponent<dex::Component::Model>("assets/models/xyz.glb", true);
    m_XYZ.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, 0, 3.5));
    m_XYZ.getComponent<dex::Component::Transform>().setScale(glm::vec3(.05));

    m_LightSphere.addComponent<dex::Component::Model>("assets/models/sphere.glb", true);
    m_LightSphere.addComponent<dex::Component::Light::Ambient>(true, glm::vec3(.3, .3, .3));
    m_LightSphere.addComponent<dex::Component::Light::Directional>(true, glm::vec3(1, 1, 1));
    m_LightSphere.getComponent<dex::Component::Transform>().setPosition(glm::vec3(-3, 4, 6));
    m_LightSphere.getComponent<dex::Component::Transform>().setScale(glm::vec3(.4));

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

    //player_trans.logAsInfo();

    float32 speed = .8 * Engine::Time.getDeltaTime();

    if (Engine::Window.Input.getKeyState(dex::Event::Key::LEFT_SHIFT))
        speed = 6 * Engine::Time.getDeltaTime();

    if (Engine::Window.Input.getKeyState(dex::Event::Key::W))
        head_trans.moveByLocal(glm::vec3(0, 0, speed));

    if (Engine::Window.Input.getKeyState(dex::Event::Key::S))
        head_trans.moveByLocal(glm::vec3(0, 0, -speed));

    if (Engine::Window.Input.getKeyState(dex::Event::Key::A))
        head_trans.moveByLocal(glm::vec3(-speed, 0, 0));

    if (Engine::Window.Input.getKeyState(dex::Event::Key::D))
        head_trans.moveByLocal(glm::vec3(speed, 0, 0));

    if (Engine::Window.Input.getKeyState(dex::Event::Key::Q))
        head_trans.moveByLocal(glm::vec3(0, -speed, 0));

    if (Engine::Window.Input.getKeyState(dex::Event::Key::E))
        head_trans.moveByLocal(glm::vec3(0, speed, 0));

    if (Engine::Window.isMouseCaptured())
    {
        const auto& m = Engine::Window.Input.getMousePosChange() * .0015;

        player_trans.rotateByEuler((glm::vec3(0, m.x, 0)));

        float max_degrees = 90;

        if (head_trans.getRotationDegrees().x <= max_degrees && head_trans.getRotationDegrees().x >= -max_degrees)
            head_trans.rotateByEulerLocal((glm::vec3(-m.y, 0, 0)));
        if (head_trans.getRotationDegrees().x >= max_degrees)
            head_trans.setRotationEuler(glm::vec3(glm::radians(max_degrees), 0, 0));
        if (head_trans.getRotationDegrees().x <= -max_degrees)
            head_trans.setRotationEuler(glm::vec3(glm::radians(-max_degrees), 0, 0));
    }

    if (Engine::Window.Input.isKeyPressed(dex::Event::Key::F11))
    {
        if (!dex::Engine::Window.isFullscreen())
            dex::Engine::Window.setFullscreen();
        else
            dex::Engine::Window.setWindowed();
    }

    if (Engine::Window.Input.isKeyPressed(dex::Event::Key::GRAVE_ACCENT))
    {
        if (dex::Engine::Window.isMouseCaptured())
            dex::Engine::Window.setCaptureMouse(false);
        else
            dex::Engine::Window.setCaptureMouse(true);
    }

    Engine::Window.Input.stopEvents();
}

void WorldLayer::render()
{
    m_Scene.render();

    static ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::Begin("Debug Window");

    ImGui::Text("Ambient Light:"); 
    ImGui::SameLine();
    ImGui::ColorEdit3("", glm::value_ptr(m_LightSphere.getComponent<dex::Component::Light::Ambient>().Color));

    ImGui::Spacing();

    ImGui::Text("Directional Light:");
    ImGui::SameLine(); // set direction in lambda transform -> direction
    ImGui::SliderFloat3("", glm::value_ptr(m_LightSphere.getComponent<dex::Component::Light::Directional>().Direction), 0, 3);

    ImGui::Text("My Delta Time: %.4f", Engine::Time.getDeltaTime());
    ImGui::End();
}
