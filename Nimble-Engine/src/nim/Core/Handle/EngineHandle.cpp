#include "EngineHandle.hpp"

#include "../NimbleEngine.hpp"

namespace nim
{
	EngineHandle::EngineHandle(NimbleEngine& engine)
		: r_Nimble(engine)
	{}
	LayerManager& EngineHandle::getLayerManager() { return r_Nimble.m_Application.m_LayerManager; }
	Window& EngineHandle::getWindow() { return r_Nimble.m_Application.m_Window; }
	Application& EngineHandle::getApplication() { return r_Nimble.m_Application; }

	void EngineHandle::shutdown() { r_Nimble.shutdown(); };
}
