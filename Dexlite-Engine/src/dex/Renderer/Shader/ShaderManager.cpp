#include "ShaderManager.hpp"

#include "ShaderBase.hpp"
#include "3D/ShaderDefault3D.hpp"

namespace dex
{
    namespace Shader
    {
        Manager::Manager()
        {
            addShader(std::make_shared<Base>());
            addShader(std::make_shared<Default3D>());
        }

        void Manager::addShader(const std::shared_ptr<Shader::Base>& shader)
        {
            m_Shaders.push_back(shader);
        }

        std::shared_ptr<Shader::Base>& Manager::getShader(const char* name)
        {
            for (auto& shader : m_Shaders)
                if (shader->getName() == name)
                    return shader;

            return m_Shaders.at(uint8(Type::BASE));
        }

        std::shared_ptr<Base>& Manager::getShader(Type type)
        {
            return m_Shaders.at(uint8(type));
        }

        void Manager::updateCurrentGlobalShaderUniforms(const GlobalUniforms& global_uniforms)
        {
            m_CurrentGlobalUniforms = global_uniforms;

            for (auto& shader : m_Shaders)
            {
                shader->updateGlobalUniforms(m_CurrentGlobalUniforms);
            }

            m_CurrentGlobalUniforms.setAllClean();
        }
    }
}
