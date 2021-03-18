#pragma once

#include "../Application/Application.hpp"
#include "../Renderer/Renderer.hpp"

namespace nim
{
	class Program;

	// Core engine.
	class NimbleEngine
	{
	public:
		NimbleEngine();
		~NimbleEngine();

		void setProgram(std::shared_ptr<Program> program);

		void run();
	public:
		bool m_Running = false;

		// Is a unique ptr because of inheritance.
		std::shared_ptr<Program> m_Program;

		Application m_Application;
		Renderer m_Renderer;
	};
}
