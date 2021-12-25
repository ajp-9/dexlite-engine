#pragma once

#include "../../Scene/Component/ModelComponent.hpp"

namespace dex
{
    struct MeshTransformation
    {
        glm::vec3 m_Translation = glm::vec3(0);
        glm::quat m_Rotation = glm::quat(glm::vec3(0.0f));
        glm::vec3 m_Scale = glm::vec3(1);
    };

    struct ModelLoader
    {
        static Component::Model loadGLTF(const std::string& location, bool binary);
    private:
        // Returns true if a mesh was found.
        static bool parseNode(MeshTransformation& meshFinalTransformation_Current, const tinygltf::Node& node, const tinygltf::Model& model);
    };
}
