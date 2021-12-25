#pragma once

#include <memory>
#include <vector>

#include <glm/mat4x4.hpp>
#include "Uniform/UniformBufferObject.hpp"

namespace dex
{
    namespace Shader
    {
        class Base;
        enum class Type : uint8_t;

        class Manager
        {
        public:
            // Initialize default shader types & default UBOs.
            Manager();

            //void addUBO(const std::shared_ptr<UniformBufferObject>& ubo);

            void addShader(const std::shared_ptr<Base>& shader);
            std::shared_ptr<Base>& getShader(const char* name);
            std::shared_ptr<Base>& getShader(Type type);

            // Global
            //void setProjectionViewMatrix(const glm::mat4& mat);
            //void setModalMatrix(const glm::mat4& mat);

            // Util
            template <typename T>
            std::shared_ptr<T> getShaderDerived(const char* name);
            template <typename T>
            std::shared_ptr<T> getShaderDerived(Type type);
        private:
            std::vector<std::shared_ptr<Base>> m_Shaders;
            std::vector<std::shared_ptr<UniformBufferObject>> m_UBOs;
        };

        enum class Type : uint8
        {
            BASE,
            DEFAULT_3D,
            TEXTURE_3D
        };

        /*
        ** Implementation:
        */

        template<typename T>
        inline std::shared_ptr<T> Manager::getShaderDerived(const char* name)
        {
            return std::static_pointer_cast<T>(getShader(name));
        }

        template<typename T>
        inline std::shared_ptr<T> Manager::getShaderDerived(Type type)
        {
            return std::static_pointer_cast<T>(getShader(type));
        }
    }
}
