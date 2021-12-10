#pragma once

#include "../../Renderer/Material/3D/MaterialDefault3D.hpp"
#include "../../Renderer/Mesh/Mesh.hpp"

namespace dex
{
    namespace Component
    {
        struct Model
        {
            Model() {}

            Model(const std::vector<Vertex3D::Default>& vertices,
                const std::vector<uint32_t>& indices,
                std::shared_ptr<Material::Default3D> material)
                : m_Mesh(vertices, indices), m_Material(material)
            {}

            Model(Mesh::Default3D mesh,
                std::shared_ptr<Material::Default3D> material)
                : m_Mesh(mesh), m_Material(material)
            {}

            void prepareRendering(const glm::mat4& model_matrix)
            {
                m_Material->m_Shader->bind();
                m_Material->m_Shader->setModelMatrix(model_matrix);

                m_Material->setUniforms(); // later batch same materials, so less uniform calls
            }

            void render()
            {
                m_Mesh.render();
            }
        public:
            std::string m_Name;

            Mesh::Default3D m_Mesh;
            std::shared_ptr<Material::Default3D> m_Material;
        };
    }
}
