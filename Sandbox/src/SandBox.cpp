#include "SandBox.hpp"

#include <entt.hpp>

#include <iostream>

#include <imgui/imgui.h>
#include <dex/Util/Logging.hpp>

using dex::Engine;

SandBox::SandBox()
    : m_World(&Window, &Renderer, Renderer.ShaderManager.getShaderDerived<dex::Shader::Default3D>(dex::Shader::Type::DEFAULT_3D))
{

}

SandBox::~SandBox()
{
}

void SandBox::beginFrame()
{
    Renderer.beginFrame();
    Renderer.clear();
}

void SandBox::update()
{
    Time.doCycle();

    m_World.update(Time.getDeltaTime());
}

void SandBox::render()
{
    m_World.render();
    m_GUI.render();
}

void SandBox::endFrame()
{
    Renderer.endFrame();
    
    Window.swapBuffers();

    Time.sleep();

    Window.Input.pollNewEvents();

    if (!Window.Open)
        Running = false;
}
