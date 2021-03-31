#include "Texture.hpp"

#include <glad/glad.h>
#include <stb_image.h>

namespace nim
{
	Texture::Texture()
	{
	}

	Texture::~Texture()
	{
	}

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE, m_ID);
	}
}
