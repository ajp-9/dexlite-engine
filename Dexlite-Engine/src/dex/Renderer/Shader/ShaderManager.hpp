#pragma once

#include <memory>
#include <vector>

#include <glm/mat4x4.hpp>
#include "../../Util/Typedefs.hpp"

#include "ShaderGlobalUniforms.hpp"

namespace dex
{
    namespace Shader
    {
        class Base;
        enum class Type : uint8_t;

        class Manager
        {
        public:
            Manager();

            void addShader(const std::shared_ptr<Base>& shader);
            std::shared_ptr<Base>& getShader(const char* name);
            std::shared_ptr<Base>& getShader(Type type);

            void updateCurrentGlobalShaderUniforms(const GlobalUniforms& global_uniforms);

            template <typename T>
            std::shared_ptr<T> getShaderDerived(const char* name) { return std::static_pointer_cast<T>(getShader(name)); }
            template <typename T>
            std::shared_ptr<T> getShaderDerived(Type type) { return std::static_pointer_cast<T>(getShader(type)); }
        private:
            std::vector<std::shared_ptr<Base>> m_Shaders;

            GlobalUniforms m_CurrentGlobalUniforms;
        };

        enum class Type : uint8
        {
            BASE,
            LINE_3D,
            DEFAULT_3D,
            TEXTURE_3D
        };
    }
}
