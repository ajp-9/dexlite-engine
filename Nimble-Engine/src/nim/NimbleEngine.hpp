#pragma once

#include "Application/Application.hpp"
#include "Renderer/Renderer.hpp"

namespace nim
{
	class NimbleEngine
	{
	public:
		NimbleEngine();
		~NimbleEngine();

		void update();
	public:
		Application application;
		Renderer renderer;
	};
}
