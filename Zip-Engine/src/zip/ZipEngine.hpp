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

		Application application;
		Renderer renderer;
	};
}
