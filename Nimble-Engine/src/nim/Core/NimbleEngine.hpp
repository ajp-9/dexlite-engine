#pragma once

#include "../Application/Application.hpp"
#include "../Renderer/Renderer.hpp"
#include "Program/Program.hpp"

namespace nim
{
	// Core engine.
	class NimbleEngine
	{
	public:
		NimbleEngine(std::shared_ptr<Program> program);
		~NimbleEngine();

		void run();
	public:
		bool m_Running = false;

		// Is a unique ptr because of inheritance.
		std::shared_ptr<Program> m_Program;

		Application m_Application;
		Renderer m_Renderer;
	};
}
