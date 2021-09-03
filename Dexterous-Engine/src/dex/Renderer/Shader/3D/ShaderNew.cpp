#include "ShaderNew.hpp"

#include <glad/glad.h>

namespace dex
{
    namespace Shader
    {
        New3D::New3D(const char* src)
            : Base(src, "New", Type::BASE)
        {
            setLocations3D();
        }

        void New3D::setLocations3D()
        {
            u_ProjectionViewMatrix_Location = glGetUniformLocation(m_ProgramID, "u_ProjectionViewMatrix");
            u_ModelMatrix_Location = glGetUniformLocation(m_ProgramID, "u_ModelMatrix");
        }

        void New3D::setProjectionViewMatrix(const glm::mat4& mat)
        {
            glUniformMatrix4fv(u_ProjectionViewMatrix_Location, 1, GL_FALSE, glm::value_ptr(mat));
        }

        void New3D::setModelMatrix(const glm::mat4& mat)
        {
            glUniformMatrix4fv(u_ModelMatrix_Location, 1, GL_FALSE, glm::value_ptr(mat));
        }
    }
}
