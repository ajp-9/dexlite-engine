#pragma once

#include <cstdint>

namespace nim
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		void bind();
	private:
		uint32_t m_ID = 0;
	};
}