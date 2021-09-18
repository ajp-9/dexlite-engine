#pragma once

#include "../Material.hpp"
#include "../Texture/Texture.hpp"
#include "../../Shader/3D/ShaderDefault3D.hpp"
#include "../../../Core/Engine.hpp"

namespace dex
{
    namespace Material
    {
        struct Default3D : Interface<Shader::Default3D>
        {
            Default3D(
                float32 texTilingFactor = 1.0f,
                const Texture& diffuseMap = Texture(),
                const Texture& specularMap = Texture())

                : // Initializer List

                Interface(Engine::renderer.shaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D), "Material::Default3D"),
                m_TexTilingFactor(texTilingFactor),
                m_DiffuseMap(diffuseMap),
                m_SpecularMap(specularMap)
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
            float32 m_TexTilingFactor;

            Texture m_DiffuseMap;
            Texture m_SpecularMap;

            bool m_DiffuseMapEnabled = false;
            bool m_SpecularMapEnabled = false;
        };
    }
}
