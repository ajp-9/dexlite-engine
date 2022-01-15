#include "GUI_Layer.hpp"

#include <imgui/imgui.h>

namespace dex
{
	GUI_Layer::GUI_Layer(const std::shared_ptr<Scene>& scene, std::shared_ptr<Entity> entity)
		: m_CurrentScene(scene), m_ViewportCamera(entity)
	{
		m_ViewportPanel.setViewportCamera(entity);

		setColorsAndStyle();

		m_ViewportCamera->addComponent<Component::Camera>(true);

		//camera.setOrthographic(5, 0.001, 100);
		m_ViewportCamera->getComponent<Component::Camera>().setPerspective(65, 0.01, 1000);

		//dex::Engine::Window.setCaptureMouse(true);

		//m_Warlock.addComponent<dex::Component::Model>("assets/models/spec_cube.glb", true);

		m_Warlock.addComponent<dex::Component::Model>("assets/models/ruff_matrix.glb", true, );
		m_Warlock.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, 0, 10));
		//m_Warlock.getComponent<dex::Component::Transform>().setRotationEuler(glm::vec3(15, 0, 0));

		m_Valdore.addComponent<dex::Component::Model>("assets/models/warlock.glb", true);
		m_Valdore.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, 0, -5));
		m_Valdore.getComponent<dex::Component::Transform>().setRotationEuler(glm::vec3(0, glm::radians(180.0), 0));
		m_Valdore.getComponent<dex::Component::Transform>().setScale(glm::vec3(.5));


		m_Triangle.addComponent<dex::Component::Model>("assets/models/plane.glb", true);
		m_Triangle.getComponent<dex::Component::Transform>().setScale(glm::vec3(10, 10, 10));
		m_Triangle.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, -5, 0));

		m_XYZ.addComponent<dex::Component::Model>("assets/models/xyz.glb", true);
		m_XYZ.getComponent<dex::Component::Transform>().setPosition(glm::vec3(-7, 0, 3.5));
		m_XYZ.getComponent<dex::Component::Transform>().setScale(glm::vec3(.05));
		//m_XYZ.addComponent<dex::Component::Light::Directional>(true, glm::vec3(.8));

		m_LightSphere.addComponent<dex::Component::Model>("assets/models/smooth_sphere.glb", true);
		m_LightSphere.addComponent<dex::Component::Light::Ambient>(true, glm::vec3(.15));
		m_LightSphere.getComponent<dex::Component::Transform>().setPosition(glm::vec3(7, 0, 3));
		m_LightSphere.getComponent<dex::Component::Transform>().setScale(glm::vec3(.4));
		m_LightSphere.addComponent<dex::Component::Light::Point>(true, glm::vec3(1, 0, 0), 1.0, .5, .45);
		//m_Head.addComponent<dex::Component::Light::Directional>(true, glm::vec3(.8));

		m_Player.addChild(*m_ViewportCamera);
		//m_Head.addComponent<dex::Component::Light::Point>(true, glm::vec3(1, 0, 0), 1.0, .5, .45);
		m_Head.getComponent<dex::Component::Transform>().setScale(glm::vec3(1002, 133, 13223));
	}

	void GUI_Layer::update()
	{
		m_CurrentScene->update();

		//m_LightSphere.getComponent<dex::Component::Transform>().rotateByEulerLocal(glm::vec3(glm::radians(.09), 0, 0));
		//m_LightSphere.getComponent<dex::Component::Transform>().rotateByEulerLocal(glm::vec3(0, -glm::radians(.09), 0));
		//m_LightSphere.getComponent<dex::Component::Transform>().rotateByEulerLocal(glm::vec3(0, 0, glm::radians(.09)));
		//m_Head.getComponent<dex::Component::Transform>().scaleByLocal(glm::vec3(1, 1, 1)); //fucks the camera

		//m_XYZ.getComponent<dex::Component::Transform>().moveBy(glm::vec3(0, 0, .001));

		auto& player_trans = m_Player.getComponent<dex::Component::Transform>();
		auto& head_trans = m_Head.getComponent<dex::Component::Transform>();

		//m_LightSphere.getComponent<dex::Component::Light::Point>().Position = player_trans.getWorldPosition();

		//player_trans.logAsInfo();

		float32 speed = .8 * Engine::Time.getDeltaTime();

		if (Engine::Window.Input.getKeyState(dex::Event::Key::LEFT_SHIFT))
			speed = 6 * Engine::Time.getDeltaTime();

		if (Engine::Window.Input.getKeyState(dex::Event::Key::W))
			player_trans.moveByLocal(glm::vec3(0, 0, speed));

		if (Engine::Window.Input.getKeyState(dex::Event::Key::S))
			player_trans.moveByLocal(glm::vec3(0, 0, -speed));

		if (Engine::Window.Input.getKeyState(dex::Event::Key::A))
			player_trans.moveByLocal(glm::vec3(-speed, 0, 0));

		if (Engine::Window.Input.getKeyState(dex::Event::Key::D))
			player_trans.moveByLocal(glm::vec3(speed, 0, 0));

		if (Engine::Window.Input.getKeyState(dex::Event::Key::Q))
			player_trans.moveByLocal(glm::vec3(0, -speed, 0));

		if (Engine::Window.Input.getKeyState(dex::Event::Key::E))
			player_trans.moveByLocal(glm::vec3(0, speed, 0));

	}

	void GUI_Layer::render()
	{
		// Note: Switch this to true to enable dockspace
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", (bool*)true, window_flags);
		ImGui::PopStyleVar();

		ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Scene"))
					true;


				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		m_SceneHierarchyPanel.render(*m_CurrentScene);
		m_ViewportPanel.render(*m_CurrentScene);
		m_InspectorPanel.render();

		ImGui::End();
	}

	void GUI_Layer::setColorsAndStyle()
	{
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.58f, 0.00f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.72f, 0.00f, 0.65f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.80f, 0.00f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.42f, 0.00f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.79f, 0.00f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.67f, 0.00f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.78f, 0.00f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.00f, 0.79f, 0.00f, 0.40f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.65f, 0.00f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.79f, 0.00f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.00f, 0.88f, 0.00f, 0.31f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.78f, 0.00f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.77f, 0.00f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.00f, 0.87f, 0.00f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.00f, 0.92f, 0.00f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 1.00f, 0.00f, 0.40f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 0.84f, 0.00f, 0.83f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 0.92f, 0.03f, 0.95f);
		colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.53f, 0.00f, 0.86f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.00f, 0.94f, 0.00f, 0.80f);
		colors[ImGuiCol_TabActive] = ImVec4(0.00f, 0.72f, 0.00f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.27f, 0.00f, 0.97f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.00f, 0.34f, 0.00f, 1.00f);
		colors[ImGuiCol_DockingPreview] = ImVec4(0.00f, 0.71f, 0.00f, 0.70f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.00f, 0.66f, 0.00f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);









		ImGuiStyle& style = ImGui::GetStyle();
		//style.
		style.WindowMinSize.x = 50.0f;
		style.WindowBorderSize = 0.0f;
	}
}
