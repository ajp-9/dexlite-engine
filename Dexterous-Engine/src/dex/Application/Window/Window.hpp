#pragma once

#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include <functional>

#include "../Event/EventBase.hpp"
#include "Input.hpp"

namespace dex
{
	namespace Layer { class Manager; }

	class Window
	{
		Window(glm::uvec2 windowDimensions);
		~Window();

		// Update window when done handling events & rendering
		void update();
	public:
		glm::ivec2 getDimensions();

		Input input;
	private:
		GLFWwindow* m_Window_GLFW = nullptr;

		friend class Engine;
		friend class ImGuiAPI;
		friend class Layer::Manager;
		friend class Input;
	};
}
