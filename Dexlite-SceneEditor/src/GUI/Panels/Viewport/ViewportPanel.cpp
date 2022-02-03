#include "ViewportPanel.hpp"

#include <imgui/imgui.h>

namespace dex
{
    ViewportPanel::ViewportPanel()
        : m_Framebuffer(glm::vec2(100, 100), { ColorAttachmentFormat::RGBA, ColorAttachmentFormat::RED_INTEGER })
    {
        
    }

    void ViewportPanel::render(CurrentScene& current_scene, Renderer& renderer)
    {
        ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_NoCollapse);

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

        m_Framebuffer.resize(glm::vec2(viewportPanelSize.x, viewportPanelSize.y));

        m_Framebuffer.bind();
        m_Framebuffer.clearAttachment(1, -1);
        renderer.clear(glm::vec4(.1, .1, .1, 1.0f));
        current_scene.Scene.render(m_Framebuffer.getSize(), renderer);
        DEX_LOG_INFO("{}", m_Framebuffer.readPixel(1, glm::ivec2(ImGui::GetMousePos().x + ImGui::GetWindowPos().x, ImGui::GetMousePos().y + ImGui::GetWindowPos().y)));
        m_Framebuffer.unbind();
        
        ImGui::Image((ImTextureID)m_Framebuffer.getColorAttachmentTexture_ID(), ImVec2(m_Framebuffer.getSize().x, m_Framebuffer.getSize().y), ImVec2(0, 1), ImVec2(1, 0));  
        
        ImGui::End();
    }
}
