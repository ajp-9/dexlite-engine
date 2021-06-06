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

		static DeltaTime s_DeltaTime;

		static Window s_Window;

		static Layer::Manager s_LayerManager;

		friend int ::main(int argc, char** argv);
	private:
		static bool s_Running;

		// Is a unique ptr because of inheritance.
		static std::shared_ptr<Program> s_Program;
	};
}
