#include "GUI.hpp"

#include <dex/Dexlite.hpp>
#include <dex/Scene/Component/Transform/TransformComponent.hpp>
#include <dex/Scene/Component/ModelComponent.hpp>
#include <dex/Util/Logging.hpp>
#include <dex/Scene/Component/LightComponents.hpp>
#include <imgui/imgui.h>

void GUI::render()
{
    static ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::Begin("Debug Window");
    ImGui::Image((ImTextureID)m_WorldHandle->framebuffer.getColorAttachmentTexture_ID(), ImVec2(m_WorldHandle->framebuffer.getSize().x, m_WorldHandle->framebuffer.getSize().y), ImVec2(0, 1), ImVec2(1, 0));

    {
        ImGui::Text("Ambient Light:");
        ImGui::SameLine();
        ImGui::ColorEdit3("a", glm::value_ptr(m_WorldHandle->m_LightSphere.getComponent<dex::Component::Light::Ambient>().Color));
    }

    ImGui::NewLine();

    {
        ImGui::Text("Directional Light2:");
        ImGui::SameLine();
        //ImGui::ColorEdit3("b", glm::value_ptr(m_LightSphere.getComponent<dex::Component::Light::Point>().Color));
    }


    {
        //ImGui::SliderFloat("Constant", &m_LightSphere.getComponent<dex::Component::Light::Point>().Constant, -5, 5);
        //ImGui::SliderFloat("Linear", &m_LightSphere.getComponent<dex::Component::Light::Point>().Linear, -5, 5);
        //ImGui::SliderFloat("Quadratic", &m_LightSphere.getComponent<dex::Component::Light::Point>().Quadratic, -5, 5);
    }


    /*ImGui::NewLine();

    ImGui::Text("Directional Light:");
    ImGui::SameLine(); // set direction in lambda transform -> direction
    ImGui::SliderFloat3("", glm::value_ptr(m_LightSphere.getComponent<dex::Component::Light::Point>().Color), -1, 1);

    ImGui::NewLine();*/

    auto& transform = m_WorldHandle->m_LightSphere.getComponent<dex::Component::Transform>();

    auto nextPosition = transform.getOrientationDegrees();

    ImGui::NewLine();
    ImGui::SliderFloat("Position X", &nextPosition.x, -360, 360);
    ImGui::SliderFloat("Position Y", &nextPosition.y, -360, 360);
    ImGui::SliderFloat("Position Z", &nextPosition.z, -360, 360);

    transform.setOrientationEuler(glm::radians(nextPosition));

    //ImGui::Text("My Delta Time: %.4f", Engine::Time.getDeltaTime());


    ImGui::End();
}
