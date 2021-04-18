#pragma once

namespace zim
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
