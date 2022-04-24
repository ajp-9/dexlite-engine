#pragma once

#include "../Material.hpp"
#include "../../Texture/Texture.hpp"
#include "../../Shader/3D/ShaderDefault3D.hpp"

namespace dex
{
    namespace Material
    {
        // culling

        struct Default3D : Base<Shader::Default3D>
        {
            Default3D(const std::shared_ptr<Shader::Default3D>& shader)
                : Base(shader)
            {}
            
            Default3D(
                const std::shared_ptr<Shader::Default3D>& shader,
                float32 texTilingFactor,
                Texture&& baseColorTexture,
                Texture&& roughnessTexture)
                
                : // Initializer List:

                Base(shader),
                m_TexTilingFactor(texTilingFactor),
                m_BaseColorTexture(std::move(baseColorTexture)),
                m_RoughnessTexture(std::move(roughnessTexture))
            {
                if (m_BaseColorTexture.isActive())
                    m_BaseColorTextureEnabled = true;

                if (m_RoughnessTexture.isActive())
                    m_RoughnessTextureEnabled = true;
            }

            Default3D(const Default3D& other) = delete;
            const Default3D& operator=(const Default3D& other) = delete;

            virtual void setUniforms()
            {
                if (m_BaseColorTextureEnabled || m_RoughnessTextureEnabled || m_EmissiveTextureEnabled)
                    m_Shader->setTexTilingFactor(m_TexTilingFactor);

                if (m_BaseColorTextureEnabled)
                {
                    m_Shader->setBaseColorTexture_Enabled(true);
                    m_BaseColorTexture.bind(0);
                }
                else
                {
                    m_Shader->setBaseColorTexture_Enabled(false);
                }

                if (m_RoughnessTextureEnabled)
                {
                    m_Shader->setRoughnessTextureEnabled(true);
                    m_RoughnessTexture.bind(1);
                }
                else
                {
                    m_Shader->setRoughnessTextureEnabled(false);
                }

                if (m_EmissiveTextureEnabled)
                {
                    m_Shader->setEmissiveTextureEnabled(true);
                    m_EmissiveTexture.bind(2);
                }
                else
                {
                    m_Shader->setEmissiveTextureEnabled(false);
                }
            }
        public:
            float32 m_TexTilingFactor = 1.0f;

            bool m_BaseColorTextureEnabled = false;
            Texture m_BaseColorTexture;

            bool m_RoughnessTextureEnabled = false;
            Texture m_RoughnessTexture;

            bool m_EmissiveTextureEnabled = false;
            Texture m_EmissiveTexture;
        };
    }
}
