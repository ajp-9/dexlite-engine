#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>

namespace dex
{
    namespace Math
    {
        glm::vec3 decomposeTransformToTranslation(const glm::mat4& matrix);
        glm::quat decomposeTransformToRotation(const glm::mat4& matrix);
        glm::vec3 decomposeTransformToScale(const glm::mat4& matrix);

        bool decomposeTransform(const glm::mat4& matrix, glm::vec3* translation = nullptr, glm::quat* rotation = nullptr, glm::vec3* scale = nullptr);
    }
}
