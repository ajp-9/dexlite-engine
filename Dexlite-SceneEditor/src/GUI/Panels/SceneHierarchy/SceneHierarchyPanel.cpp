#include "SceneHierarchyPanel.hpp"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <string>
#include <dex/Util/Logging.hpp>
#include <dex/Dexlite.hpp>

namespace dex
{
    SceneHierarchyPanel::SceneHierarchyPanel(CurrentScene* current_scene)
        : m_CurrentScene(current_scene)
    {
    }

    void SceneHierarchyPanel::render()
    {
        ImGui::Begin("Scene Hierarchy", (bool*)0, ImGuiWindowFlags_NoCollapse);
        
        auto root_children = m_CurrentScene->Scene.m_Root->getChildren();

        for (auto& child : root_children)
            renderEntityNode(child);
        
        ImGui::End();
    }
     
    void SceneHierarchyPanel::renderEntityNode(Entity& entity)
    {
        auto& children = entity.getChildren();

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

        if (!entity.getChildrenHandles().size())
            flags |= ImGuiTreeNodeFlags_Bullet;

        if (m_CurrentScene->SelectedEntity == entity)
            flags |= ImGuiTreeNodeFlags_Selected;

        if (ImGui::TreeNodeEx(entity.getComponent<Component::Tag>().m_Tag.c_str(), flags))
        {
            for (auto& child : children)
                renderEntityNode(child);

            ImGui::TreePop();
        }

        if (ImGui::IsItemClicked())
        {
            m_CurrentScene->SelectedEntity = entity;
        }

        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Add Child Entity"))
            {
                DEX_LOG_CRITICAL("{}", entity.operator entt::entity());
            }

            if (ImGui::MenuItem("Delete"))
            {
                entity.destroy();
            }

            ImGui::EndPopup();
        }
    }
}
