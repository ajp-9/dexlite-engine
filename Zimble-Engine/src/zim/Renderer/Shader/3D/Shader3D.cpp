#include "Shader3D.hpp"

#include <glad/glad.h>

namespace zim
{
	namespace Shader
	{
		Shader3D::Shader3D(const char* src, const char* name)
			: Shader(src, name, Type::DEFAULT)
		{
			setLocations3D();
		}

		void Shader3D::setLocations3D()
		{
			u_ProjectionViewMatrix_Location = glGetUniformLocation(m_ProgramID, "u_ProjectionViewMatrix");
			u_ModelMatrix_Location = glGetUniformLocation(m_ProgramID, "u_ModelMatrix");
		}

		void Shader3D::setProjectionViewMatrix(const glm::mat4& mat)
		{
			glUniformMatrix4fv(u_ProjectionViewMatrix_Location, 1, GL_FALSE, glm::value_ptr(mat));
		}

		void Shader3D::setModelMatrix(const glm::mat4& mat)
		{
			glUniformMatrix4fv(u_ModelMatrix_Location, 1, GL_FALSE, glm::value_ptr(mat));
		}
	}
}
