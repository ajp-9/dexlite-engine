#pragma once

#include "../../../Renderer/Material/3D/MaterialDefault3D.hpp"
#include "../../../Util/Transform/Transform.hpp"
#include "../../../Renderer/Mesh/Mesh.hpp"
#include "../Transform/TransformComponent.hpp"
#include "../BaseComponent.hpp"

namespace dex
{
    namespace Component
    {
        struct Model : Base
        {
            Model(
                const Entity& entity,
                const std::vector<Vertex3D::Default>& vertices,
                const std::vector<uint32_t>& indices,
                std::shared_ptr<Material::Default3D> material)

                : // Initializer List:

                Base(entity),
                m_Mesh(vertices, indices),
                m_Material(material)
            {
                m_Enabled = true;
            }

            Model(
                const Entity& entity,
                Mesh::Default3D mesh,
                std::shared_ptr<Material::Default3D> material)

                : // Initializer List:

                Base(entity),
                m_Mesh(std::move(mesh)),
                m_Material(material)
            {
                m_Enabled = true;
            }

            Model(const Entity& entity, const std::string& location, bool binary)
                : Base(entity)
            {
                loadGLTF(location, binary);

                m_Enabled = true;
            }

            inline void prepareRendering()
            {
                if (m_Enabled)
                {
                    m_Material->m_Shader->bind();
                    m_Material->m_Shader->setModelMatrix(m_Entity.getComponent<Component::Transform>().getTransformationMatrix());

                    m_Material->setUniforms(); // later batch same materials, so less uniform calls
                }
            }

            inline void render()
            {
                if (m_Enabled)
                    m_Mesh.render();
            }
        private:
            void loadGLTF(const std::string& location, bool binary);
            
            // Returns true if a mesh was found.
            bool parseNode(glm::mat4& meshTransformationMatrix_Current, const tinygltf::Node& node, const tinygltf::Model& model);
        public:
            Mesh::Default3D m_Mesh;
            std::shared_ptr<Material::Default3D> m_Material;

            bool m_Enabled = false;
        };
    }
}
