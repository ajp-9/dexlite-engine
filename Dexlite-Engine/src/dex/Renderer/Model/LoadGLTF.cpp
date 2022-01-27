#include "LoadGLTF.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/vec3.hpp>

namespace dex
{
    bool parseNode(glm::mat4& meshTransformationMatrix_Current, const tinygltf::Node& node, const tinygltf::Model& model);

    Model LoadGLTF(const std::string& file_location, const std::shared_ptr<Shader::Default3D> shader_default_3d)
    {
        tinygltf::Model model;
        tinygltf::TinyGLTF loader;
        std::string warn;
        std::string error;

        bool ret = false;
        if (file_location.substr(file_location.find_last_of(".") + 1) == "glb")
            ret = loader.LoadBinaryFromFile(&model, &error, &warn, file_location);
        else
            DEX_LOG_ERROR("<dex::loadGLTF()>: Only binary GLTF files (.glb) can be used.");

        //ret = loader.LoadASCIIFromFile(&model, &error, &warn, file_location);

        if (!warn.empty())
            DEX_LOG_WARN("<ModelLoader::loadGLTF()>: {}", warn);

        if (!error.empty())
        {
            DEX_LOG_ERROR("<ModelLoader::loadGLTF()>: {}", error);

            return Model();
        }

        if (!ret)
        {
            DEX_LOG_ERROR("<ModelLoader::loadGLTF()>: Failed to load model.");

            return Model();
        }

        if (model.meshes.size() != 1)
        {
            DEX_LOG_ERROR("<ModelLoader::loadGLTF()>: Only 1 mesh per model.");

            return Model();
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

                glm::vec4 baseColor = glm::vec4(1.0f);
                float roughness = 1.0f;

                if (model.materials.size())
                {
                    const auto& raw_baseColor = model.materials[primitive.material].pbrMetallicRoughness.baseColorFactor;
                    baseColor = glm::vec4(raw_baseColor.at(0), raw_baseColor.at(1), raw_baseColor.at(2), raw_baseColor.at(3));

                    roughness = model.materials[primitive.material].pbrMetallicRoughness.roughnessFactor;
                }

                if (primitive.attributes.find("POSITION") != primitive.attributes.end())
                {
                    const tinygltf::Accessor& accessor = model.accessors[primitive.attributes["POSITION"]];
                    const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
                    const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];

                    const float* raw_positions = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);

                    for (size_t i = 0; i < accessor.count; ++i)
                    {
                        positions.emplace_back(glm::vec3(raw_positions[i * 3 + 0], raw_positions[i * 3 + 1], -raw_positions[i * 3 + 2]));
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
                        normals.emplace_back(glm::vec3(raw_normals[i * 3 + 0], raw_normals[i * 3 + 1], -raw_normals[i * 3 + 2]));
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

                    vertex.Position = positions[i];

                    vertex.Color = baseColor;
                    vertex.Roughness = roughness;

                    if (positions.size() == normals.size())
                        vertex.Normal = normals[i];
                    if (positions.size() == texCoords.size())
                        vertex.TexCoord = texCoords[i];

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
                    DEX_LOG_ERROR("<ModelLoader::loadGLTF()>: Indices doesn't have the correct component type.");
                }

                largest_index = *std::max_element(indices.begin(), indices.end());
            }
        }

        std::shared_ptr<dex::Material::Default3D> material = std::make_shared<dex::Material::Default3D>(shader_default_3d);

        //material->Roughness = roughness;

        //material->m_Shader = default_3d_shader;

        for (auto& mat : model.materials)
        {
            if (mat.pbrMetallicRoughness.baseColorTexture.index != -1)
            {
                if (!material->m_BaseColorTextureEnabled)
                {
                    const tinygltf::Texture& texture = model.textures[mat.pbrMetallicRoughness.baseColorTexture.index];
                    const tinygltf::Image& image = model.images[model.textures[mat.pbrMetallicRoughness.baseColorTexture.index].source];

                    material->m_BaseColorTexture = Texture(image.image, model.samplers[texture.sampler], glm::ivec2(image.width, image.height), (image.component == 4) ? GL_RGBA : (image.component == 3) ? GL_RGB : 0, true);
                    material->m_BaseColorTextureEnabled = true;
                }
                else
                {
                    DEX_LOG_ERROR("<dex::ModelLoader::loadGLTF()>: Only 1 diffuse texture.");
                }
            }

            if (mat.pbrMetallicRoughness.metallicRoughnessTexture.index != -1)
            {
                if (!material->m_RoughnessTextureEnabled)
                {
                    const tinygltf::Texture& texture = model.textures[mat.pbrMetallicRoughness.metallicRoughnessTexture.index];
                    const tinygltf::Image& image = model.images[model.textures[mat.pbrMetallicRoughness.metallicRoughnessTexture.index].source];

                    material->m_RoughnessTexture = Texture(image.image, model.samplers[texture.sampler], glm::ivec2(image.width, image.height), (image.component == 4) ? GL_RGBA : (image.component == 3) ? GL_RGB : 0, true);
                    material->m_RoughnessTextureEnabled = true;
                }
                else
                {
                    DEX_LOG_ERROR("<dex::ModelLoader::loadGLTF()>: Only 1 roughness texture.");
                }
            }

            if (mat.emissiveTexture.index != -1)
            {
                if (!material->m_EmissiveTextureEnabled)
                {
                    const tinygltf::Texture& texture = model.textures[mat.emissiveTexture.index];
                    const tinygltf::Image& image = model.images[model.textures[mat.emissiveTexture.index].source];

                    material->m_EmissiveTexture = Texture(image.image, model.samplers[texture.sampler], glm::ivec2(image.width, image.height), (image.component == 4) ? GL_RGBA : (image.component == 3) ? GL_RGB : 0, true);
                    material->m_EmissiveTextureEnabled = true;
                }
                else
                {
                    DEX_LOG_ERROR("<dex::ModelLoader::loadGLTF()>: Only 1 emissive texture.");
                }
            }

        }

        glm::mat4 meshTransformationMatrix_Final = glm::mat4(1.0f);

        for (auto& scene : model.scenes)
        {
            for (auto& node_loc : scene.nodes)
            {
                glm::mat4 meshFinalTransformationMatrix_Temp = glm::mat4(1.0f);

                if (parseNode(meshFinalTransformationMatrix_Temp, model.nodes.at(node_loc), model))
                    meshTransformationMatrix_Final = meshFinalTransformationMatrix_Temp;
            }
        }

        for (auto& vertex : vertices)
        {
            vertex.Position = meshTransformationMatrix_Final * glm::vec4(vertex.Position, 1.0f);
            vertex.Normal = glm::mat3(glm::transpose(glm::inverse(meshTransformationMatrix_Final))) * vertex.Normal;
        }

        return Model(Mesh::Default3D(vertices, indices), material);
    }

    bool parseNode(glm::mat4 & meshTransformationMatrix_Current, const tinygltf::Node & node, const tinygltf::Model & model)
    {
        if (node.translation.size() == 3 || node.rotation.size() == 4 || node.scale.size() == 3)
        {
            glm::vec3 translation = glm::vec3(0);
            glm::quat rotation = glm::quat(glm::vec3(0.0f));
            glm::vec3 scale = glm::vec3(1.0f);

            if (node.translation.size() == 3)
                translation = glm::vec3(node.translation.at(0), node.translation.at(1), -node.translation.at(2));

            if (node.rotation.size() == 4)
            {
                const auto& eRot = glm::eulerAngles(
                    glm::quat(
                        float(node.rotation.at(3)),
                        float(node.rotation.at(0)),
                        float(node.rotation.at(1)),
                        float(node.rotation.at(2))
                    )
                );

                rotation = glm::quat(glm::vec3(-eRot.x, -eRot.y, eRot.z));
            }

            if (node.scale.size() == 3)
                scale = glm::vec3(node.scale.at(0), node.scale.at(1), node.scale.at(2));

            meshTransformationMatrix_Current =
                meshTransformationMatrix_Current *
                glm::translate(glm::mat4(1.0f), translation) *
                glm::toMat4(rotation) *
                glm::scale(glm::mat4(1.0f), scale);
        }

        if (node.mesh != -1)
        {
            return true;
        }
        else
        {
            for (auto& child_node_loc : node.children)
            {
                glm::mat4 meshFinalTransformationMatrix_Temp = meshTransformationMatrix_Current;

                if (parseNode(meshFinalTransformationMatrix_Temp, model.nodes.at(child_node_loc), model))
                {
                    meshTransformationMatrix_Current = meshFinalTransformationMatrix_Temp;

                    return true;
                }
            }
        }

        return false;
    }
}
