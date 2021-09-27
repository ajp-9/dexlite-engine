#include "ModelLoader.hpp"

#include <tiny_gltf.h>

#include "../../Util/Logging.hpp"

namespace dex
{
    Component::Model ModelLoader::loadGLTF(const char* location, bool binary)
    {
        tinygltf::Model model;
        tinygltf::TinyGLTF loader;
        std::string warn;
        std::string error;

        bool ret = false;
        if (binary)
            ret = loader.LoadBinaryFromFile(&model, &error, &warn, location);
        else
            ret = loader.LoadASCIIFromFile(&model, &error, &warn, location);

        if (!warn.empty())
            DEX_LOG_WARN("<ModelLoader::loadGLTF>: {}", warn);

        if (!error.empty())
        {
            DEX_LOG_ERROR("<ModelLoader::loadGLTF>: {}", error);
            return Component::Model();
        }

        if (!ret)
        {
            DEX_LOG_ERROR("<ModelLoader::loadGLTF>: Failed to load model.");
            return Component::Model();
        }

        if (model.meshes.size() != 1)
        {
            DEX_LOG_ERROR("<ModelLoader::loadGLTF>: Only 1 mesh per model.");
            return Component::Model();
        }

        std::vector<Vertex3D::Default> vertices;
        std::vector<uint32> indices;
        
        for (auto& mesh : model.meshes)
        {
            uint32 largest_index = -1;
            
            for (auto& primitive : mesh.primitives)
            {
                std::vector<glm::vec3> positions;
                std::vector<glm::vec3> normals;
                std::vector<glm::vec2> texCoords;
                glm::vec4 baseColor = glm::vec4(1);
                
                //glm::vec3 real_angle = glm::eulerAngles(glm::quat(model.nodes[0].rotation[0], model.nodes[0].rotation[1], model.nodes[0].rotation[2], model.nodes[0].rotation[3]));

                if (model.materials.size())
                {
                    const auto& raw_baseColor = model.materials[primitive.material].pbrMetallicRoughness.baseColorFactor;
                    baseColor = glm::vec4(raw_baseColor.at(0), raw_baseColor.at(1), raw_baseColor.at(2), raw_baseColor.at(3));
                }

                if (primitive.attributes.find("POSITION") != primitive.attributes.end())
                {
                    const tinygltf::Accessor& accessor = model.accessors[primitive.attributes["POSITION"]];
                    const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
                    const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];

                    const float* raw_positions = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);

                    for (size_t i = 0; i < accessor.count; ++i)
                    {
                        positions.emplace_back(glm::vec3(raw_positions[i * 3 + 0], raw_positions[i * 3 + 1], raw_positions[i * 3 + 2]));
                    }
                }

                if (primitive.attributes.find("NORMAL") != primitive.attributes.end())
                {
                    const tinygltf::Accessor& accessor = model.accessors[primitive.attributes["NORMAL"]];
                    const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
                    const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];

                    const float* raw_normals = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);

                    for (size_t i = 0; i < accessor.count; ++i)
                    {
                        normals.emplace_back(glm::vec3(raw_normals[i * 3 + 0], raw_normals[i * 3 + 1], raw_normals[i * 3 + 2]));
                    }
                }

                if (primitive.attributes.find("TEXCOORD_0") != primitive.attributes.end())
                {
                    const tinygltf::Accessor& accessor = model.accessors[primitive.attributes["TEXCOORD_0"]];
                    const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
                    const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];

                    const float* raw_texCoords = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);

                    for (size_t i = 0; i < accessor.count; ++i)
                    {
                        texCoords.emplace_back(glm::vec2(raw_texCoords[i * 2 + 0], raw_texCoords[i * 2 + 1]));
                    }
                }

                for (size_t i = 0; i < positions.size(); i++)
                {
                    Vertex3D::Default vertex;

                    vertex.m_Position = positions[i];
                    vertex.m_Color = baseColor;

                    if (positions.size() == normals.size())
                        vertex.m_Normal = normals[i];
                    if (positions.size() == texCoords.size())
                        vertex.m_TexCoord = texCoords[i];

                    vertices.push_back(vertex);
                }

                const tinygltf::Buffer& buffer = model.buffers[model.bufferViews[primitive.indices].buffer];
                const tinygltf::Accessor& accessor = model.accessors[primitive.indices];
                
                if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
                {
                    const uint16* bufferIndices = reinterpret_cast<const uint16*>(&buffer.data.at(0) + model.bufferViews[primitive.indices].byteOffset);

                    for (size_t i = 0; i < accessor.count; i++)
                        indices.emplace_back(bufferIndices[i] + largest_index + 1);
                }
                else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
                {
                    const uint32* bufferIndices = reinterpret_cast<const uint32*>(&buffer.data.at(0) + model.bufferViews[primitive.indices].byteOffset);

                    for (size_t i = 0; i < accessor.count; i++)
                        indices.emplace_back(bufferIndices[i] + largest_index + 1);
                }
                else
                {
                    DEX_LOG_ERROR("<ModelLoader::loadGLTF>: Indices doesn't have the correct component type.");
                }

                largest_index = *std::max_element(indices.begin(), indices.end());
            }
        }

        std::shared_ptr<dex::Material::Default3D> material = std::make_shared<dex::Material::Default3D>();

        for (auto& mat : model.materials)
        {
            if (mat.pbrMetallicRoughness.baseColorTexture.index != -1)
            {
                {
                    const auto& texture = model.images[model.textures[mat.pbrMetallicRoughness.baseColorTexture.index].source];


                    material->m_DiffuseMap = Texture(texture.image, glm::ivec2(texture.width, texture.height), texture.image.size() / (size_t(texture.width) * size_t(texture.height)), true);
                    material->m_DiffuseMapEnabled = true;
                }
                {
                    //DEX_LOG_ERROR("<ModelLoader::loadGLTF>: Only 1 texture for baseColorTexture.");
                }
            }
        }

        return Component::Model(dex::Mesh::Default3D(vertices, indices), material);
    }
}
