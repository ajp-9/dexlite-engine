#include "Renderer.hpp"

#include <glad/glad.h>

#include "../Scene/Component/ModelComponent.hpp"
#include "../Scene/Component/TransformComponent.hpp"

namespace dex
{
    Renderer::Renderer(glm::uvec4 viewport)
    {
        glEnable(GL_DEPTH_TEST);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //glFrontFace(GL_CW);
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);
        glClearColor(.1, .1, .1, 1.0f); // Clear the color buffer
    }

    Renderer::~Renderer()
    {

    }

    void Renderer::beginFrame()
    {
        m_ImGuiAPI.beginFrame();
    }

    void Renderer::endFrame()
    {
        m_ChangeProjectionMatrixNext = false;

        m_ImGuiAPI.endFrame();
    }

    void Renderer::update()
    {
    }

    void Renderer::setViewportSize(glm::uvec2 size)
    {
        m_ChangeProjectionMatrixNext = true;
        std::cout << size.x << '\n';
        m_ScreenDimensions = size;
        glViewport(0, 0, m_ScreenDimensions.x, m_ScreenDimensions.y);
    }

    /*void Renderer::setViewportPosition(glm::uvec2 position)
    {
        m_Viewport = glm::uvec4(position.x, position.y, m_Viewport.z, m_Viewport.w);
        glViewport(0, 0, m_Viewport.z, m_Viewport.w);
    }*/

    void Renderer::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void Renderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::renderScene(Scene& scene)
    {
        auto& shader = shaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D);

        scene.findNSetActiveCamera();
        
        if (m_ChangeProjectionMatrixNext)
            scene.m_Registry.get<Component::Camera>(scene.m_ActiveCameraID).updateProjectionMatrix();
        
        shader->setProjectionViewMatrix(scene.m_Registry.get<Component::Camera>(scene.m_ActiveCameraID).getProjectionViewMatrix());

        auto& model_view = scene.m_Registry.view<Component::Model>();
        
        for (auto& entityID : model_view)
        {
            auto& model = scene.m_Registry.get<Component::Model>(entityID);
            model.prepareRendering(scene.m_Registry.get<Component::Transform>(entityID));
            model.render();
        }
    }
}
