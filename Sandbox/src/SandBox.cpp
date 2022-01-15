#include "SandBox.hpp"

#include <entt.hpp>

#include <iostream>

#include <imgui/imgui.h>
#include <dex/Util/Logging.hpp>

using dex::Engine;

SandBox::SandBox()
    : m_WorldLayer(Window, Renderer.ShaderManager.getShaderDerived<dex::Shader::Default3D>(dex::Shader::Type::DEFAULT_3D))
{

}

SandBox::~SandBox()
{
}

void SandBox::beginFrame()
{
    Renderer.clear();
    Renderer.beginFrame();
}

void SandBox::update()
{
    Time.doCycle();

    m_WorldLayer.update(Window, Time.getDeltaTime());
}

void SandBox::render()
{
    m_WorldLayer.render(Renderer, Window);
}

void SandBox::endFrame()
{
    Renderer.endFrame();
    
    Window.swapBuffers();

    Window.Input.pollNewEvents();

    Time.sleep();

    if (!Window.Open)
        Running = false;
}
