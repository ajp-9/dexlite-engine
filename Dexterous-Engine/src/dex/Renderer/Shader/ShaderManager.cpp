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

            //auto modelUBO = std::make_unique<UniformBufferObject>("ubo_ModelMatrix");
            //modelUBO.bindShader(getShader(Type::BASE));
            //modelUBO->bindShader(getShader(Type::DEFAULT_3D));
            
            //std::cout << sizeof(__declspec(align(16)) int) << " eee\n";

            //UniformBufferObject("ubo_ModelMatrix").bindShader(getShader(Type::DEFAULT_3D));
        }

        void Manager::addUBO(const std::shared_ptr<UniformBufferObject>& ubo)
        {
            m_UBOs.emplace_back(ubo);
        }

        void Manager::addShader(const std::shared_ptr<Shader::Base>& shader)
        {
            m_Shaders.emplace_back(shader);
        }

        std::shared_ptr<Shader::Base>& Manager::getShader(const char* name)
        {
            for (auto& shader : m_Shaders)
                if (shader->getName() == name)
                    return shader;
        }

        std::shared_ptr<Base>& Manager::getShader(Type type)
        {
            return m_Shaders.at(uint8_t(type));
        }

        void Manager::setProjectionViewMatrix(const glm::mat4& mat)
        {
            //for (auto& shader : m_Shaders)
            //    shader->setProjectionViewMatrix(mat);
        }

        void Manager::setModalMatrix(const glm::mat4& mat)
        {
        }
    }
}
