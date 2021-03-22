#pragma once

namespace nim
{
	namespace gl
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
}