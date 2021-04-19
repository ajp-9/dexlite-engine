#pragma once

#include <cstdint>

namespace dex
{
	class Texture
	{
	public:
		Texture(const char* src, bool blending = true);
		~Texture();

		void bind();
		void unbind();
	private:
		uint32_t m_ID = 0;
	};
}