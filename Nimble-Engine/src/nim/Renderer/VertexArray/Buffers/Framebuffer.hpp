#pragma once

namespace nim
{
	class Framebuffer
	{
		Framebuffer();
		~Framebuffer();

		void bind();
		void unbind();

		void resize();
	};
	
}
