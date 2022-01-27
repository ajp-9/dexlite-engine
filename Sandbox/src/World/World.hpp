#pragma once

#include <dex/Core/Engine.hpp>
#include <dex/Dexlite.hpp>
#include <dex/Renderer/Framebuffer/Framebuffer.hpp>

class World
{
    dex::Window* Window = nullptr;
    dex::Renderer* Renderer = nullptr;
public:
    World(dex::Window* window, dex::Renderer* renderer, const std::shared_ptr<dex::Shader::Default3D>& shader);

    void update(const float delta_time);
    void render();
private:
    dex::Scene m_Scene;

    dex::Entity m_Player = { &m_Scene, "Player"};
    dex::Entity m_Head = { &m_Scene, "Head"};

    dex::Entity m_XYZ = { &m_Scene, "XYZ"};
    dex::Entity m_Warlock = { &m_Scene, "Warlock"};
    dex::Entity m_Valdore = { &m_Scene, "Valdore" };
    dex::Entity m_LightSphere = { &m_Scene, "Light Sphere" };
    dex::Entity m_Triangle = { &m_Scene, "Triangle" };

    dex::Framebuffer framebuffer = dex::Framebuffer(glm::vec2(150, 150));
public:
    friend class GUI;
};
