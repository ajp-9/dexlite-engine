#pragma once

namespace dex
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
