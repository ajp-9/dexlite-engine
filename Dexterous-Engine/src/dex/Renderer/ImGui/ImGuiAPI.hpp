#pragma once

namespace dex
{
	class ImGuiAPI
	{
	public:
		ImGuiAPI();
		~ImGuiAPI();

		void beginFrame();
		void endFrame();
	};
}
