#include "ViewportPanel.hpp"

#include <imgui/imgui.h>

namespace dex
{
    ViewportPanel::ViewportPanel(dex::Window* window, Renderer* renderer, CurrentScene* current_scene)
        : m_Window(window), m_Renderer(renderer), m_CurrentScene(current_scene), m_Framebuffer(glm::vec2(100, 100), { ColorAttachmentFormat::RGBA, ColorAttachmentFormat::RED_INTEGER })
    {
        
    }

    void ViewportPanel::update()
    {
    }

    void ViewportPanel::render()
    {
        ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_NoCollapse);

        auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
        auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
        auto viewportOffset = ImGui::GetWindowPos();
        m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
        m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

        m_Framebuffer.resize(glm::vec2(viewportPanelSize.x, viewportPanelSize.y));

        m_Framebuffer.bind();

        m_Framebuffer.clearAttachment(0, glm::vec4(.1, .1, .1, 1.0f));
        m_Framebuffer.clearAttachmentRed(1, -1);

        m_Framebuffer.drawBuffers();

        m_CurrentScene->Scene.render(m_Framebuffer.getSize(), *m_Renderer, m_CurrentScene->m_ViewportCameraHead);

        auto [mx, my] = ImGui::GetMousePos();
        mx -= m_ViewportBounds[0].x;
        my -= m_ViewportBounds[0].y;
        glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
        my = viewportSize.y - my;
        int mouseX = (int)mx;
        int mouseY = (int)my;

        if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
        {
            //ImGui::SetWindowFocus();
            
            if (m_Window->Input.isMouseReleased(Event::MouseButton::LEFT) && ImGui::IsWindowFocused())
                m_CurrentScene->SelectedEntity = Entity((entt::entity)m_Framebuffer.readPixel(1, glm::ivec2(mouseX, mouseY)), &m_CurrentScene->Scene);

            if (m_Window->Input.getMouseState(Event::MouseButton::MIDDLE))
                m_Window->setCaptureMouse(true);

            if (m_Window->Input.getMouseState(Event::MouseButton::RIGHT))
                m_Window->setCaptureMouse(true);
        }

        if (m_Window->Input.isMouseReleased(Event::MouseButton::MIDDLE))
            m_Window->setCaptureMouse(false);


        if (m_Window->Input.isMouseReleased(Event::MouseButton::RIGHT))
            m_Window->setCaptureMouse(false);

        m_Framebuffer.unbind();
        
        ImGui::Image((ImTextureID)m_Framebuffer.getColorAttachmentTexture_ID(), ImVec2(m_Framebuffer.getSize().x, m_Framebuffer.getSize().y), ImVec2(0, 1), ImVec2(1, 0));  
        
        ImGui::End();
    }
}
