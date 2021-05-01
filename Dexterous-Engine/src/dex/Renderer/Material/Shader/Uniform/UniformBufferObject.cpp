#include "UniformBufferObject.hpp"

#include <glad/glad.h>

namespace dex
{
	UniformBufferObject::UniformBufferObject()
	{
		glGenBuffers(1, &m_ID);
		bind();
	}

	void UniformBufferObject::setLayout(const std::vector<Data::Type>& types)
	{

	}

	void UniformBufferObject::bind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
	}

	void UniformBufferObject::unbind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}
