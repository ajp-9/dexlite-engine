#include "ImGuiLayer.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>

#include "../../Renderer/ImGui/ImGuiAPI.hpp"

namespace nim
{
	void ImGuiLayer::Attach() {}

	void ImGuiLayer::Detach() {}

	void ImGuiLayer::event(std::unique_ptr<event::Event>& e)
	{
		ImGui_ImplSDL2_ProcessEvent(&e->m_RawEvent);
		if (e->m_Type == event::type::KEYBOARD || e->m_Type == event::type::KEY_DOWN || e->m_Type == event::type::KEY_UP)
			e->m_Handled = ImGui::GetIO().WantCaptureKeyboard;
		if (e->m_Type == event::type::MOUSE_MOVE || e->m_Type == event::type::MOUSE_DOWN || e->m_Type == event::type::MOUSE_UP || e->m_Type == event::type::MOUSE_SCROLL)
			e->m_Handled = ImGui::GetIO().WantCaptureMouse;
	}
}
