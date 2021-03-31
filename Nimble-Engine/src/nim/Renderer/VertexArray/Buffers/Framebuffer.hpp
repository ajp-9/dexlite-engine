#pragma once

namespace nim
{
	namespace GL
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
