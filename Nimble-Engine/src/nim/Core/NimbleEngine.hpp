#pragma once

#include "../Util/Time/DeltaTime.hpp"
#include "../Application/Application.hpp"
#include "../Renderer/Renderer.hpp"
#include "Program/Program.hpp"

int main(int argc, char** argv);

namespace nim
{

	// Core engine.
	class NimbleEngine
	{
		static void Init(std::shared_ptr<Program> program);
		static void Shutdown();

		static void run();
		static void shutdown();
	public:
		static bool m_Running;

		// Is a unique ptr because of inheritance.
		static std::shared_ptr<Program> m_Program;

		static DeltaTime m_DeltaTime;

		static Application m_Application;
		static Renderer m_Renderer;
	public:
		friend int ::main(int argc, char** argv);
		friend class EventManager;
	};
}
