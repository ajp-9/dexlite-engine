#pragma once

namespace nim
{
	class ImGuiAPI
	{
	public:
		static void Init();
		static void Shutdown();

		static void beginFrame();
		static void endFrame();
	};
}
