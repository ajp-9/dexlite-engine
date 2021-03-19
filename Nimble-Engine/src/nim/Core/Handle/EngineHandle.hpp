#pragma once

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

		LayerManager& getLayerManager();
		Window& getWindow();
		Application& getApplication();

		void shutdown();

	private:
		NimbleEngine& r_Nimble;
	};
}
