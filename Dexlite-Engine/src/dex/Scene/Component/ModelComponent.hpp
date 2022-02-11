#pragma once

#include "BaseComponent.hpp"
#include "../../Renderer/Model/Model.hpp"
#include "Transform/TransformComponent.hpp"

namespace dex
{
    namespace Component
    {
        struct Model : dex::Model
        {
            Model() = default;

            Model(dex::Model&& model)
                : dex::Model(std::move(model))
            {
                Enabled = true;
            }

            inline void prepareRendering(const entt::entity& handle, const Component::Transform& transform)
            {
                if (Enabled)
                {
                    Material->m_Shader->bind();
                    Material->m_Shader->setEntityID((int32)handle);
                    Material->m_Shader->setModelMatrix(transform.getTransformationMatrix());

                    Material->setUniforms(); // later batch same materials, so less uniform calls
                }
            }

            inline void render()
            {
                if (Enabled)
                    Mesh.render();
            }
        public:
            bool Enabled = false;
        };
    }
}
