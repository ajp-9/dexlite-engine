#pragma once

#include "../NimbleEngine.hpp"

namespace nim
{
	class NimbleEngine;

	class LayerManager;
	class Window;
	class Application;

	// Interface for the program to send instructions to the engine.
	class EngineHandle
	{
	public:
		EngineHandle(NimbleEngine& engine);

		LayerManager& getLayerManager() { return r_Nimble.m_Application.m_LayerManager; }
		Window& getWindow() { return r_Nimble.m_Application.m_Window; }
		Application& getApplication() { return r_Nimble.m_Application; }

	private:
		NimbleEngine& r_Nimble;
	};
}
