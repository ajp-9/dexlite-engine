#include "WorldLayer.hpp"

#include <dex/Application/Event/KeyEvent.hpp>

#include <dex/Scene/Component/Transform/TransformComponent.hpp>
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

    //m_Warlock.addComponent<dex::Component::Model>("assets/models/spec_cube.glb", true);
    
    m_Warlock.addComponent<dex::Component::Model>("assets/models/ruff_matrix.glb", true);
    m_Warlock.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, 0, 10));
    //m_Warlock.getComponent<dex::Component::Transform>().setRotationEuler(glm::vec3(15, 0, 0));

    m_Valdore.addComponent<dex::Component::Model>("assets/models/warlock.glb", true);
    m_Valdore.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, 0, -5));
    m_Valdore.getComponent<dex::Component::Transform>().setRotationEuler(glm::vec3(0, glm::radians(180.0), 0));
    m_Valdore.getComponent<dex::Component::Transform>().setScale(glm::vec3(.5));


    m_Triangle.addComponent<dex::Component::Model>("assets/models/plane.glb", true);
    m_Triangle.getComponent<dex::Component::Transform>().setScale(glm::vec3(10, 10, 10));
    m_Triangle.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, -5, 0));

    m_XYZ.addComponent<dex::Component::Model>("assets/models/xyz.glb", true);
    m_XYZ.getComponent<dex::Component::Transform>().setPosition(glm::vec3(-7, 0, 3.5));
    m_XYZ.getComponent<dex::Component::Transform>().setScale(glm::vec3(.05));
    //m_XYZ.addComponent<dex::Component::Light::Directional>(true, glm::vec3(.8));

    m_LightSphere.addComponent<dex::Component::Model>("assets/models/smooth_sphere.glb", true);
    m_LightSphere.addComponent<dex::Component::Light::Ambient>(true, glm::vec3(.15));
    m_LightSphere.getComponent<dex::Component::Transform>().setPosition(glm::vec3(7, 0, 3));
    m_LightSphere.getComponent<dex::Component::Transform>().setScale(glm::vec3(.4));
    m_LightSphere.addComponent<dex::Component::Light::Point>(true, glm::vec3(1, 0, 0), 1.0, .5, .45);
    //m_Head.addComponent<dex::Component::Light::Directional>(true, glm::vec3(.8));

    m_Player.addChild(m_Head);
    m_Head.getComponent<dex::Component::Transform>().setScale(glm::vec3(1002, 133, 13223));
    //m_Head.addChild(m_Triangle);
    //m_Head.addChild(m_LightSphere);

    //m_Head.addChild(m_XYZ);
    //m_Warlock.addChild(m_XYZ);
}

void WorldLayer::Detach()
{
}

void WorldLayer::update()
{
    m_Scene.update();

    //m_LightSphere.getComponent<dex::Component::Transform>().rotateByEulerLocal(glm::vec3(glm::radians(.09), 0, 0));
    //m_LightSphere.getComponent<dex::Component::Transform>().rotateByEulerLocal(glm::vec3(0, -glm::radians(.09), 0));
    //m_LightSphere.getComponent<dex::Component::Transform>().rotateByEulerLocal(glm::vec3(0, 0, glm::radians(.09)));
    //m_Head.getComponent<dex::Component::Transform>().scaleByLocal(glm::vec3(1, 1, 1)); //fucks the camera

    //m_XYZ.getComponent<dex::Component::Transform>().moveBy(glm::vec3(0, 0, .001));

    auto& player_trans = m_Player.getComponent<dex::Component::Transform>();
    auto& head_trans = m_Head.getComponent<dex::Component::Transform>();

    //m_LightSphere.getComponent<dex::Component::Light::Point>().Position = player_trans.getWorldPosition();

    //player_trans.logAsInfo();

    float32 speed = .8 * Engine::Time.getDeltaTime();

    if (Engine::Window.Input.getKeyState(dex::Event::Key::LEFT_SHIFT))
        speed = 6 * Engine::Time.getDeltaTime();

    if (Engine::Window.Input.getKeyState(dex::Event::Key::W))
        player_trans.moveByLocal(glm::vec3(0, 0, speed));

    if (Engine::Window.Input.getKeyState(dex::Event::Key::S))
        player_trans.moveByLocal(glm::vec3(0, 0, -speed));

    if (Engine::Window.Input.getKeyState(dex::Event::Key::A))
        player_trans.moveByLocal(glm::vec3(-speed, 0, 0));

    if (Engine::Window.Input.getKeyState(dex::Event::Key::D))
        player_trans.moveByLocal(glm::vec3(speed, 0, 0));

    if (Engine::Window.Input.getKeyState(dex::Event::Key::Q))
        player_trans.moveByLocal(glm::vec3(0, -speed, 0));

    if (Engine::Window.Input.getKeyState(dex::Event::Key::E))
        player_trans.moveByLocal(glm::vec3(0, speed, 0));

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
    //dex::Engine::Renderer.enableDepthTest();

    framebuffer.bind();
    m_Scene.render(framebuffer.getSize());
    framebuffer.unbind();

    m_Scene.render(Engine::Window.getDimensions());

    static ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::Begin("Debug Window");
    ImGui::Image((ImTextureID)framebuffer.getColorAttachmentTexture_ID(), ImVec2(framebuffer.getSize().x, framebuffer.getSize().y), ImVec2(0, 1), ImVec2(1, 0));

    {
        ImGui::Text("Ambient Light:");
        ImGui::SameLine();
        ImGui::ColorEdit3("a", glm::value_ptr(m_LightSphere.getComponent<dex::Component::Light::Ambient>().Color));
    }

    ImGui::NewLine();

    {
        ImGui::Text("Directional Light2:");
        ImGui::SameLine();
        //ImGui::ColorEdit3("b", glm::value_ptr(m_LightSphere.getComponent<dex::Component::Light::Point>().Color));
    }


    {
        //ImGui::SliderFloat("Constant", &m_LightSphere.getComponent<dex::Component::Light::Point>().Constant, -5, 5);
        //ImGui::SliderFloat("Linear", &m_LightSphere.getComponent<dex::Component::Light::Point>().Linear, -5, 5);
        //ImGui::SliderFloat("Quadratic", &m_LightSphere.getComponent<dex::Component::Light::Point>().Quadratic, -5, 5);
    }
    

    /*ImGui::NewLine();

    ImGui::Text("Directional Light:");
    ImGui::SameLine(); // set direction in lambda transform -> direction
    ImGui::SliderFloat3("", glm::value_ptr(m_LightSphere.getComponent<dex::Component::Light::Point>().Color), -1, 1);

    ImGui::NewLine();*/

    auto& transform = m_LightSphere.getComponent<dex::Component::Transform>();

    auto nextPosition = transform.getRotationDegrees();

    ImGui::NewLine();
    ImGui::SliderFloat("Position X", &nextPosition.x, -360, 360);
    ImGui::SliderFloat("Position Y", &nextPosition.y, -360, 360);
    ImGui::SliderFloat("Position Z", &nextPosition.z, -360, 360);

    transform.setRotationEuler(glm::radians(nextPosition));

    ImGui::Text("My Delta Time: %.4f", Engine::Time.getDeltaTime());


    ImGui::End();
}
