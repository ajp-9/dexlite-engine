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
        int mouseX = (int)mx;
        int mouseY = (int)my;

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

        if (!m_Window->isMouseCaptured())
        {
            if (m_Window->Input.isKeyPressed(Event::Key::W))
                m_ActiveGuizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
            if (m_Window->Input.isKeyPressed(Event::Key::E))
                m_ActiveGuizmoOperation = ImGuizmo::OPERATION::ROTATE;
            if (m_Window->Input.isKeyPressed(Event::Key::R))
                m_ActiveGuizmoOperation = ImGuizmo::OPERATION::SCALE;

        }



        if (m_CurrentScene->SelectedEntity.isValid())
        {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();

            ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());

            const auto& camera = m_CurrentScene->ViewportCameraHead.getComponent<Component::Camera>();

            glm::mat4 cam_proj = camera.getProjectionMatrix();
            glm::mat4 cam_view = camera.getViewMatrix();

            auto& trans_comp =  m_CurrentScene->SelectedEntity.getComponent<Component::Transform>();
            auto trans_matrix = trans_comp.getTransformationMatrix();
            
            //ImGuizmo::DrawGrid(glm::value_ptr(cam_view),
            //    glm::value_ptr(cam_proj), glm::value_ptr(glm::mat4(1.0f)), 10.f);

            auto trans_delta = glm::mat4(1.0f);
                /*glm::translate(glm::mat4(1.0f), trans_comp.getPosition()) *
                glm::toMat4(trans_comp.getOrientationQuat()) *
                glm::scale(glm::mat4(1.0f), trans_comp.getScale());*/

            //ImGuizmo::dex::ManipulateSeperated(
            ImGuizmo::Manipulate(
                glm::value_ptr(cam_view),
                glm::value_ptr(cam_proj),
                m_ActiveGuizmoOperation,
                ImGuizmo::MODE::LOCAL,
                glm::value_ptr(trans_matrix),
                glm::value_ptr(trans_delta));

            if (ImGuizmo::IsUsing())
            {
                glm::vec3 transform;
                glm::vec3 orientation;
                glm::vec3 scale;

                //Math::decomposeTransform(trans_matrix, &transform, &orientation, &scale);
                ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(trans_delta), glm::value_ptr(transform), glm::value_ptr(orientation), glm::value_ptr(scale));
                //ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(w), glm::value_ptr(transform), glm::value_ptr(orientation), glm::value_ptr(scale));

                //DEX_LOG_INFO(transform.x);

                DEX_LOG_INFO("X: {}, Y: {}, Z: {}", transform.x, transform.y, transform.z);

                trans_comp.moveBy(transform);
                //trans_comp.setPosition(transform);
                //trans_comp.moveByLocal(transform - trans_comp.getWorldPosition());

                //trans_comp.rotateByQuat(glm::radians(orientation));
                //trans_comp.setScale(scale);
            }
        }


        ImGui::End();
    }
}
