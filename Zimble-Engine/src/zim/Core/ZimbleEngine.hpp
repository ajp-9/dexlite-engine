#pragma once

#include "../Util/Time/DeltaTime.hpp"
#include "../Application/Window/Window.hpp"
#include "../Application/Layer/LayerManager.hpp"
#include "../Renderer/Renderer.hpp"
#include "Program/Program.hpp"
#include "EntryPoint.hpp"

namespace zim
{
	// Core engine.
	class ZimbleEngine
	{
		static void Init(std::shared_ptr<Program> program);
		static void Shutdown();

		static void run();
	public:
		static DeltaTime m_DeltaTime;

		static Window m_Window;
		static LayerManager m_LayerManager;

		friend class EventManager;
		friend int ::main(int argc, char** argv);
	private:
		static bool m_Running;

		// Is a unique ptr because of inheritance.
		static std::shared_ptr<Program> m_Program;
	};
}
