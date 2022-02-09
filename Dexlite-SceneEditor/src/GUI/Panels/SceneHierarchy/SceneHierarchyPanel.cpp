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
        bool deleted = false;

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

        if (!entity.getChildren().size())
            flags |= ImGuiTreeNodeFlags_Bullet;

        if (m_CurrentScene->SelectedEntity == entity)
            flags |= ImGuiTreeNodeFlags_Selected;

        bool open = ImGui::TreeNodeEx((const void*)entity.getHandle(), flags, entity.getComponent<Component::Tag>().m_Tag.c_str());

        if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
        {
            m_CurrentScene->SelectedEntity = entity;
        }

        if (ImGui::BeginPopupContextItem())
        {
            m_CurrentScene->SelectedEntity = entity;

            if (ImGui::MenuItem("Add Child Entity"))
            {
                entity.addNewChild("New Child");
            }

            if (ImGui::MenuItem("Delete"))
            {
                deleted = true;
            }

            ImGui::EndPopup();
        }

        if (open)
        {
            for (auto& child : children)
                renderEntityNode(child);

            ImGui::TreePop();
        }

        if (deleted)
            entity.destroy();
    }
}
