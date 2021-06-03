#pragma once

#include "../Util/Time/DeltaTime.hpp"
#include "../Application/Window/Window.hpp"
#include "../Application/Layer/LayerManager.hpp"
#include "../Renderer/Renderer.hpp"
#include "Program/Program.hpp"
#include "Program/EntryPoint.hpp"

namespace dex
{
	// Core engine.
	class Engine
	{
		static void Init(std::shared_ptr<Program> program);
		static void Shutdown();

		static void Run();
	public:
		static void Stop();

		static DeltaTime m_DeltaTime;

		static Window m_Window;

		static Layer::Manager m_LayerManager;
		static Event::Manager m_EventManager;

		friend int ::main(int argc, char** argv);
	private:
		static bool m_Running;

		// Is a unique ptr because of inheritance.
		static std::shared_ptr<Program> m_Program;
	};
}
