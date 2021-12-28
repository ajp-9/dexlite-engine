#pragma once

#include "../../Renderer/Material/3D/MaterialDefault3D.hpp"
#include "../../Renderer/Mesh/Mesh.hpp"
#include "BaseComponent.hpp"

namespace dex
{
    class Entity;

    namespace Component
    {
        struct Model : Base
        {
            Model() = default;

            Model(
                const std::vector<Vertex3D::Default>& vertices,
                const std::vector<uint32_t>& indices,
                std::shared_ptr<Material::Default3D> material)

                : // Initializer List:

                m_Mesh(vertices, indices),
                m_Material(material)
            {
                m_Enabled = true;
            }

            Model(
                Mesh::Default3D mesh,
                std::shared_ptr<Material::Default3D> material)

                : // Initializer List:

                m_Mesh(std::move(mesh)),
                m_Material(material)
            {
                m_Enabled = true;
            }

            void prepareRendering(const glm::mat4& model_matrix)
            {
                if (m_Enabled)
                {
                    m_Material->m_Shader->bind();
                    m_Material->m_Shader->setModelMatrix(model_matrix);

                    m_Material->setUniforms(); // later batch same materials, so less uniform calls
                }
            }

            void render()
            {
                if (m_Enabled)
                    m_Mesh.render();
            }
        public:
            Mesh::Default3D m_Mesh;
            std::shared_ptr<Material::Default3D> m_Material; /// hmmm make entity in base n make comp::mat

            bool m_Enabled = false;
        public:
            friend class dex::Entity;
        };
    }
}
