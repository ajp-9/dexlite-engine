#include "ViewportPanel.hpp"

#include <imgui/imgui.h>
#include <dex/Util/Math/Math.hpp>

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

        m_CurrentScene->Scene.render(m_Framebuffer.getSize(), *m_Renderer, m_CurrentScene->ViewportCameraHead);

        auto [mx, my] = ImGui::GetMousePos();
        mx -= m_ViewportBounds[0].x;
        my -= m_ViewportBounds[0].y;
        glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
        my = viewportSize.y - my;
        int mouseX = static_cast<int>(mx);
        int mouseY = static_cast<int>(my);

        if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
        {
            if (m_Window->Input.isMouseReleased(Event::MouseButton::LEFT) && ImGui::IsWindowFocused() && !ImGuizmo::IsUsing())
                m_CurrentScene->SelectedEntity = Entity((entt::entity)m_Framebuffer.readPixel(1, glm::ivec2(mouseX, mouseY)), &m_CurrentScene->Scene);

            if (m_Window->Input.getMouseState(Event::MouseButton::MIDDLE))
            {
                m_CurrentScene->CurrentViewportState = CurrentScene::ViewportCameraState::PAN;
                ImGui::SetWindowFocus();
            }

            if (m_Window->Input.getMouseState(Event::MouseButton::RIGHT))
            {
                m_CurrentScene->CurrentViewportState = CurrentScene::ViewportCameraState::FPS;
                m_Window->setCaptureMouse(true);
                ImGui::SetWindowFocus();
            }
        }

        if (m_Window->Input.isMouseReleased(Event::MouseButton::MIDDLE))
        {
            m_CurrentScene->CurrentViewportState = CurrentScene::ViewportCameraState::NONE;
        }

        if (m_Window->Input.isMouseReleased(Event::MouseButton::RIGHT))
        {
            m_CurrentScene->CurrentViewportState = CurrentScene::ViewportCameraState::NONE;
            m_Window->setCaptureMouse(false);
        }

        m_Framebuffer.unbind();
        
        ImGui::Image((ImTextureID)m_Framebuffer.getColorAttachmentTexture_ID(), ImVec2(m_Framebuffer.getSize().x, m_Framebuffer.getSize().y), ImVec2(0, 1), ImVec2(1, 0));  
        
        // Guizmo:

        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();

        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);

        if (ImGui::IsWindowFocused() && !m_Window->isMouseCaptured())
        {
            if (m_Window->Input.isKeyPressed(Event::Key::W))
                m_ActiveGuizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
            if (m_Window->Input.isKeyPressed(Event::Key::E))
                m_ActiveGuizmoOperation = ImGuizmo::OPERATION::ROTATE;
            if (m_Window->Input.isKeyPressed(Event::Key::R))
                m_ActiveGuizmoOperation = ImGuizmo::OPERATION::SCALE;
        }

        const auto& camera = m_CurrentScene->ViewportCameraHead.getComponent<Component::Camera>();

        glm::mat4 cam_proj = camera.getProjectionMatrix();
        glm::mat4 cam_view = camera.getViewMatrix();

        //ImGuizmo::DrawGrid(glm::value_ptr(cam_view), glm::value_ptr(cam_proj), glm::value_ptr(glm::mat4(1.0f)), 50.0f);

        if (m_CurrentScene->SelectedEntity.isValid())
        {
            auto& trans_comp = m_CurrentScene->SelectedEntity.getComponent<Component::Transform>();
            auto trans_matrix = trans_comp.getTransformationMatrix();

            // Snapping
            bool enable_snap = m_Window->Input.getKeyState(Event::Key::LEFT_SHIFT);

            float snapValue = 1.0f;
            if (m_ActiveGuizmoOperation == ImGuizmo::OPERATION::ROTATE)
                snapValue = 45.0f;

            float snapValues[3] = { snapValue, snapValue, snapValue };

            ImGuizmo::Manipulate(
                glm::value_ptr(cam_view),
                glm::value_ptr(cam_proj),
                m_ActiveGuizmoOperation,
                ImGuizmo::MODE::LOCAL,
                glm::value_ptr(trans_matrix),
                (float*)0,
                enable_snap ? snapValues : (const float*)0);
            
            if (ImGuizmo::IsUsing())
            {
                glm::vec3 transform = {};
                glm::quat orientation = {};
                glm::vec3 scale = {};

                trans_matrix = glm::inverse(trans_comp.m_ParentTransformationMatrix) * trans_matrix;
                
                //ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(trans_matrix), glm::value_ptr(transform), glm::value_ptr(orientation), glm::value_ptr(scale));

                Math::decomposeTransform(trans_matrix, &transform, &orientation, &scale);

                trans_comp.setPosition(transform);
                trans_comp.setOrientationQuat(orientation);
                trans_comp.setScale(scale);
            }
        }

        ImGui::End();
    }
}
