#pragma once

#include "Application/Application.hpp"
#include "Renderer/Renderer.hpp"

namespace zip
{
	class ZipEngine
	{
	public:
		ZipEngine();
		~ZipEngine();

		void update();
	public:
		Application application;
		Renderer renderer;
	};
}
