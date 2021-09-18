#include "ShaderDefault3D.hpp"

#include <glad/glad.h>

namespace dex
{
    namespace Shader
    {
        Default3D::Default3D(const char* src)
            : Base(src, "Shader::Default3D", Type::DEFAULT_3D)
        {
            m_TexTilingFactor_Location = glGetUniformLocation(m_ProgramID, "u_TexTilingFactor");

            m_DiffuseMapSampler_Location = glGetUniformLocation(m_ProgramID, "u_DiffuseMapSampler");
            m_DiffuseMapEnabled_Location = glGetUniformLocation(m_ProgramID, "u_DiffuseMapEnabled");

            m_SpecularMapSampler_Location = glGetUniformLocation(m_ProgramID, "u_SpecularMapSampler");
            m_SpecularMapEnabled_Location = glGetUniformLocation(m_ProgramID, "u_SpecularMapEnabled");

            setLocations3D();

            glUniform1i(m_DiffuseMapSampler_Location, 0); // replacing functions....... for GL_TEX_0,1,2,3,4
            glUniform1i(m_SpecularMapSampler_Location, 1);
        }

        void Default3D::setLocations3D()
        {
            m_ProjectionViewMatrix_Location = glGetUniformLocation(m_ProgramID, "u_ProjectionViewMatrix");
            m_ModelMatrix_Location = glGetUniformLocation(m_ProgramID, "u_ModelMatrix");
        }

        void Default3D::setProjectionViewMatrix(const glm::mat4& mat)
        {
            glUniformMatrix4fv(m_ProjectionViewMatrix_Location, 1, GL_FALSE, glm::value_ptr(mat));
        }

        void Default3D::setModelMatrix(const glm::mat4& mat)
        {
            glUniformMatrix4fv(m_ModelMatrix_Location, 1, GL_FALSE, glm::value_ptr(mat));
        }

        void Default3D::setTexTilingFactor(float tiling_factor)
        {
            glUniform1f(m_TexTilingFactor_Location, tiling_factor);
        }

        void Default3D::setDiffuseMapEnabled(bool enabled)
        {
            glUniform1i(m_DiffuseMapEnabled_Location, enabled);
        }

        void Default3D::setDiffuseMapSampler()
        {
            glUniform1i(m_DiffuseMapSampler_Location, 0);
        }

        void Default3D::setSpecularMapEnabled(bool enabled)
        {
            glUniform1i(m_SpecularMapEnabled_Location, enabled);
        }

        void Default3D::setSpecularMapSampler()
        {
            glUniform1i(m_SpecularMapSampler_Location, 1);
        }
    }
}
