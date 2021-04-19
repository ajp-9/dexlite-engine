#include "ShaderInterface3D.hpp"

#include <glad/glad.h>

namespace dex
{
	namespace Shader
	{
		Interface3D::Interface3D(const char* src, const char* name)
			: Base(src, name, Type::DEFAULT)
		{
			setLocations3D();
		}

		void Interface3D::setLocations3D()
		{
			u_ProjectionViewMatrix_Location = glGetUniformLocation(m_ProgramID, "u_ProjectionViewMatrix");
			u_ModelMatrix_Location = glGetUniformLocation(m_ProgramID, "u_ModelMatrix");
		}

		void Interface3D::setProjectionViewMatrix(const glm::mat4& mat)
		{
			glUniformMatrix4fv(u_ProjectionViewMatrix_Location, 1, GL_FALSE, glm::value_ptr(mat));
		}

		void Interface3D::setModelMatrix(const glm::mat4& mat)
		{
			glUniformMatrix4fv(u_ModelMatrix_Location, 1, GL_FALSE, glm::value_ptr(mat));
		}
	}
}
