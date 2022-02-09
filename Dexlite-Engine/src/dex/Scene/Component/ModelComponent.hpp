#pragma once

#include "BaseComponent.hpp"
#include "../../Renderer/Model/Model.hpp"
#include "Transform/TransformComponent.hpp"

namespace dex
{
    namespace Component
    {
        struct Model : dex::Model, Base
        {
            Model(const Entity& own_entity)
                : Base(own_entity)
            {}

            Model(
                const Entity& own_entity,
                dex::Model&& model)

                : // Initializer List:

                Base(own_entity),
                dex::Model(std::move(model))
            {
                Enabled = true;
            }

            inline void prepareRendering()
            {
                if (Enabled)
                {
                    Material->m_Shader->bind();
                    Material->m_Shader->setEntityID((int32)OwnEntity.getHandle());
                    Material->m_Shader->setModelMatrix(OwnEntity.getComponent<Component::Transform>().getTransformationMatrix());

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
