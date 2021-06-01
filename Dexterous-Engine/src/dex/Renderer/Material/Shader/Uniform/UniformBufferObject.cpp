#include "UniformBufferObject.hpp"

#include <glad/glad.h>

namespace dex
{
	UniformBufferObject::UniformBufferObject()
	{
		glGenBuffers(1, &m_ID);
		bind();

		m_BlockBinding = s_NextBlockBinding++;
		std::cout << m_BlockBinding << ", " << s_NextBlockBinding << "\n";
	}

	void UniformBufferObject::bindShader(const std::shared_ptr<Shader::Base>& shader, const char* ubo_name)
	{
		m_InternalBlockBinding = glGetUniformBlockIndex(shader->getID(), ubo_name);
		glUniformBlockBinding(shader->getID(), m_InternalBlockBinding, m_BlockBinding);
		glGetActiveUniformBlockiv(shader->getID(), m_InternalBlockBinding, GL_UNIFORM_BLOCK_DATA_SIZE, &m_BlockSize);
	}

	void UniformBufferObject::bind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
	}

	void UniformBufferObject::unbind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	/*
	** Initialize Static Memeber Variables
	*/

	uint32_t UniformBufferObject::s_NextBlockBinding = 0;
}
