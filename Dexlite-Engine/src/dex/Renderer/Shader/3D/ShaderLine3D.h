#pragma once

#include "../ShaderBase.hpp"
#include <glad/gl.h>
#include "../../../Util/Logging.hpp"

namespace dex
{
    namespace Shader
    {
        class Line3D : public Base
        {
        public:
            Line3D(const std::string& src = "assets/shaders/3d/line.glsl")
                : Base(src, "dex::Shader::Line3D", Type::LINE_3D)
            {
                bind();

                m_ProjectionViewMatrix_Location = glGetUniformLocation(m_ProgramID, "u_ProjectionViewMatrix");
            }

            virtual void updateGlobalUniforms(const GlobalUniforms& global_uniforms) override
            {
                if (global_uniforms.isProjectionViewMatrixDirty())
                    setProjectionViewMatrix(global_uniforms.getProjectionViewMatrix());
            }

            void setProjectionViewMatrix(const glm::mat4& mat)
            {
                glUniformMatrix4fv(m_ProjectionViewMatrix_Location, 1, GL_FALSE, glm::value_ptr(mat));
            }
        private:
            GLuint m_ProjectionViewMatrix_Location;
        };
    }
}
