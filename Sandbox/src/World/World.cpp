#include "World.hpp"

#include <dex/Application/Event/KeyEvent.hpp>

#include <dex/Scene/Component/Transform/TransformComponent.hpp>
#include <imgui/imgui.h>
#include <dex/Util/Logging.hpp>
#include <dex/Scene/Component/LightComponents.hpp>

#include <filesystem>

World::World(dex::Window* window, dex::Renderer* renderer, const std::shared_ptr<dex::Shader::Default3D>& shader)
    : Window(window), Renderer(renderer)
{
    auto& camera = m_Head.addComponent<dex::Component::Camera>(true);

    //camera.setOrthographic(5, 0.001, 100);
    camera.setPerspective(65.0f, 0.01f, 1000.0f);
    
    Window->setCaptureMouse(true);

    auto wat = glm::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f);

    //m_Warlock.addComponent<dex::Component::Model>("assets/models/spec_cube.glb", true);

    m_Warlock.addComponent<dex::Component::Model>(dex::LoadGLTF("assets/models/ruff_matrix.glb", shader));
    m_Warlock.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, 0, 10));
    //m_Warlock.getComponent<dex::Component::Transform>().setRotationEuler(glm::vec3(15, 0, 0));

    //auto m = dex::LoadGLTF("assets/models/ruff_matrix.glb", shader);

    m_Valdore.addComponent<dex::Component::Model>(dex::LoadGLTF("assets/models/warlock.glb", shader));
    m_Valdore.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, 0, -5));
    m_Valdore.getComponent<dex::Component::Transform>().setOrientationEuler(glm::vec3(0, glm::radians(180.0), 0));
    m_Valdore.getComponent<dex::Component::Transform>().setScale(glm::vec3(.5));


    m_Triangle.addComponent<dex::Component::Model>(dex::LoadGLTF("assets/models/plane.glb", shader));
    m_Triangle.getComponent<dex::Component::Transform>().setScale(glm::vec3(10, 10, 10));
    m_Triangle.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, -5, 0));

    m_XYZ.addComponent<dex::Component::Model>(dex::LoadGLTF("assets/models/xyz.glb", shader));
    m_XYZ.getComponent<dex::Component::Transform>().setPosition(glm::vec3(-7, 0, 3.5));
    m_XYZ.getComponent<dex::Component::Transform>().setScale(glm::vec3(.05f));
    //m_XYZ.addComponent<dex::Component::Light::Directional>(true, glm::vec3(.8));

    m_LightSphere.addComponent<dex::Component::Model>(dex::LoadGLTF("assets/models/smooth_sphere.glb", shader));
    m_LightSphere.addComponent<dex::Component::Light::Ambient>(true, glm::vec3(.15f));
    m_LightSphere.getComponent<dex::Component::Transform>().setPosition(glm::vec3(7, 0, 3));
    m_LightSphere.getComponent<dex::Component::Transform>().setScale(glm::vec3(.4f));
    m_LightSphere.addComponent<dex::Component::Light::Point>(true, glm::vec3(1, 0, 0), 1.0, .5, .45);
    //m_Head.addComponent<dex::Component::Light::Directional>(true, glm::vec3(.8));

    m_Player.addChild(m_Head);
    m_Head.addComponent<dex::Component::Light::Point>(true, glm::vec3(1, 0, 0), 1.0, .5, .45);
    m_Head.getComponent<dex::Component::Transform>().setScale(glm::vec3(1002, 133, 13223));
    //m_Head.addChild(m_Triangle);
    //m_Head.addChild(m_LightSphere);

    //m_Head.addChild(m_XYZ);
    //m_Warlock.addChild(m_XYZ);
}

void World::update(const float delta_time)
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

    float32 speed = .8 * delta_time;

    if (Window->Input.getKeyState(dex::Event::Key::LEFT_SHIFT))
        speed = 6 * delta_time;

    if (Window->Input.getKeyState(dex::Event::Key::W))
        player_trans.moveByLocal(glm::vec3(0, 0, speed));

    if (Window->Input.getKeyState(dex::Event::Key::S))
        player_trans.moveByLocal(glm::vec3(0, 0, -speed));

    if (Window->Input.getKeyState(dex::Event::Key::A))
        player_trans.moveByLocal(glm::vec3(-speed, 0, 0));

    if (Window->Input.getKeyState(dex::Event::Key::D))
        player_trans.moveByLocal(glm::vec3(speed, 0, 0));

    if (Window->Input.getKeyState(dex::Event::Key::Q))
        player_trans.moveByLocal(glm::vec3(0, -speed, 0));

    if (Window->Input.getKeyState(dex::Event::Key::E))
        player_trans.moveByLocal(glm::vec3(0, speed, 0));

    if (Window->isMouseCaptured())
    {
        const auto& m = Window->Input.getMousePosChange() * .0015;

        player_trans.rotateByEuler((glm::vec3(0, m.x, 0)));

        float max_degrees = 90;

        if (head_trans.getOrientationDegrees().x <= max_degrees && head_trans.getOrientationDegrees().x >= -max_degrees)
            head_trans.rotateByEulerLocal((glm::vec3(-m.y, 0, 0)));
        if (head_trans.getOrientationDegrees().x >= max_degrees)
            head_trans.setOrientationEuler(glm::vec3(glm::radians(max_degrees), 0, 0));
        if (head_trans.getOrientationDegrees().x <= -max_degrees)
            head_trans.setOrientationEuler(glm::vec3(glm::radians(-max_degrees), 0, 0));
    }

    if (Window->Input.isKeyPressed(dex::Event::Key::F11))
    {
        if (!Window->isFullscreen())
            Window->setFullscreen();
        else
            Window->setWindowed();
    }

    if (Window->Input.isKeyPressed(dex::Event::Key::GRAVE_ACCENT))
    {
        if (Window->isMouseCaptured())
            Window->setCaptureMouse(false);
        else
            Window->setCaptureMouse(true);
    }

    Window->Input.stopEvents();
}

void World::render()
{
    framebuffer.bind();
    Renderer->clear();
    m_Scene.render(framebuffer.getSize(), *Renderer);
    framebuffer.unbind();

    m_Scene.render(Window->getDimensions(), *Renderer);
}
