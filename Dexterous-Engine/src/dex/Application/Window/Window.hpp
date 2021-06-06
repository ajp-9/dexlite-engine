#pragma once

#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>

#include "../Layer/Event/EventBase.hpp"

namespace dex
{
	namespace Layer { class Manager; }

	class Window
	{
		Window(glm::uvec2 windowDimensions);
		~Window();

		void update();
	public:
		glm::ivec2 getDimensions();
	private:
		GLFWwindow* m_Window_GLFW = nullptr;

		friend class Engine;
		friend class ImGuiAPI;
		friend class Layer::Manager;

		using EventCallback = std::function<void(Event::Base&)>;

		struct Data
		{
			std::string m_Title;
			glm::uvec2 m_Dimensions;
			bool m_VSync;

			EventCallback m_EventCallbackFunc;
		};

		Data m_Data;
	};
}
