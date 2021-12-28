#pragma once

#include "../Material.hpp"
#include "../Texture/Texture.hpp"
#include "../../Shader/3D/ShaderDefault3D.hpp"
#include "../../../Core/Engine.hpp"

namespace dex
{
    namespace Material
    {
        struct Default3D : Base<Shader::Default3D>
        {
            Default3D()
                : Base(Engine::Renderer.ShaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D))
            {}
            
            Default3D(
                float32 texTilingFactor,
                Texture&& diffuseMap,
                Texture&& specularMap)
                
                : // Initializer List:

                Base(Engine::Renderer.ShaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D)),
                m_TexTilingFactor(texTilingFactor),
                m_DiffuseMap(std::move(diffuseMap)),
                m_SpecularMap(std::move(specularMap))
            {
                if (m_DiffuseMap.isActive())
                    m_DiffuseMapEnabled = true;

                if (m_SpecularMap.isActive())
                    m_SpecularMapEnabled = true;
            }

            virtual void setUniforms()
            {
                if (m_DiffuseMapEnabled || m_SpecularMapEnabled)
                    m_Shader->setTexTilingFactor(m_TexTilingFactor);

                if (m_DiffuseMapEnabled)
                {
                    m_Shader->setDiffuseMapEnabled(true);
                    m_DiffuseMap.bind();
                }
                else
                    m_Shader->setDiffuseMapEnabled(false);

                if (m_SpecularMapEnabled)
                    m_Shader->setSpecularMapEnabled(true);
                else
                    m_Shader->setSpecularMapEnabled(false);
            }
        public:
            float32 m_TexTilingFactor = 1.0f;

            Texture m_DiffuseMap;
            Texture m_SpecularMap;

            bool m_DiffuseMapEnabled = false;
            bool m_SpecularMapEnabled = false;
        };
    }
}
