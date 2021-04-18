#pragma once

namespace zim
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
