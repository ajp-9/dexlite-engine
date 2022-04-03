#include "Math.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include "../Time/Stopwatch.hpp"

#include "../Logging.hpp"

namespace dex
{
    namespace Math
    {
        void decomposeTransform(const glm::mat4& matrix, glm::vec3* translation, glm::quat* orientation, glm::vec3* scale)
        {
            glm::mat4 mat = matrix;
    
            if (scale != nullptr)
            {
                scale->x = glm::length(mat[0]);
                scale->y = glm::length(mat[1]);
                scale->z = glm::length(mat[2]);
            }

            if (orientation != nullptr)
            {
                // Normalize ortho
                mat[0] = glm::normalize(mat[0]);
                mat[1] = glm::normalize(mat[1]);
                mat[2] = glm::normalize(mat[2]);

                glm::vec3 rotation = {};
                
                rotation.x = glm::atan (mat[1][2], mat[2][2]);
                rotation.y = glm::atan(-mat[0][2], glm::sqrt(mat[1][2] * mat[1][2] + mat[2][2] * mat[2][2]));
                rotation.z = glm::atan (mat[0][1], mat[0][0]);

                *orientation = glm::quat(rotation);
            }

            if (translation != nullptr)
            {
                *translation = mat[3];
            }
        }
    }
}
