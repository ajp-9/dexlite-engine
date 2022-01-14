#include "ViewportPanel.hpp"

#include <imgui/imgui.h>

namespace dex
{
    ViewportPanel::ViewportPanel()
        : m_Framebuffer(glm::vec2(100, 100))
    {
        
    }

    void ViewportPanel::render(Scene& scene)
    {
        ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_NoCollapse);

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();



        m_Framebuffer.resize(glm::vec2(viewportPanelSize.x, viewportPanelSize.y));

        m_Framebuffer.bind();
        scene.render(m_Framebuffer.getSize());
        m_Framebuffer.unbind();

        ImGui::Image((ImTextureID)m_Framebuffer.getColorAttachmentTexture_ID(), ImVec2(m_Framebuffer.getSize().x, m_Framebuffer.getSize().y), ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
    }
}