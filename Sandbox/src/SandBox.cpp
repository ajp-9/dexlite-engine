#include "SandBox.hpp"

#include "Layers/WorldLayer.hpp"

#include <entt.hpp>

#include <iostream>

#include <dex/Scene/Component/TransformComponent.hpp>
#include "Layers/DebugLayer.hpp"
#include <imgui/imgui.h>
#include <dex/Scene/Component/ModelComponent.hpp>

#include <tiny_gltf.h>

using dex::Engine;

void SandBox::Init()
{
    Engine::layerManager.pushLayer(std::make_shared<WorldLayer>());
    Engine::layerManager.pushLayer(std::make_shared<DebugLayer>());

    m_Player = m_Scene.createEntity();
    m_Entity = m_Scene.createEntity();

    auto& camera = m_Player.addComponent<dex::Component::Camera>(true);
    
    //camera.setOrthographic(5, 0.001, 100);
    camera.setPerspective(60, .001, 1000);

    camera.updateProjectionMatrix();
    camera.updateViewMatrix();

    std::vector<dex::Vertex3D::Default> vertices;/* =
    {
        dex::Vertex3D::Default(glm::vec3(1, 1, 0), glm::vec3(0, 0, 0), glm::vec4(0, 1, 0, 1), glm::vec2(1, 1)),
        dex::Vertex3D::Default(glm::vec3(1, -1, 0),   glm::vec3(0, 0, 0), glm::vec4(1, 0, 0, 1), glm::vec2(1, 0)),
        dex::Vertex3D::Default(glm::vec3(-1, -1, 0),  glm::vec3(0, 0, 0), glm::vec4(0, 0, 1, 1), glm::vec2(0, 0)),
        dex::Vertex3D::Default(glm::vec3(-1, 1, 0),  glm::vec3(0, 0, 0), glm::vec4(0, 1, 1, 1), glm::vec2(0, 1))
    };*/

    std::vector<uint32> indices/* = std::vector<uint32>{0, 1, 3, 1, 2, 3}*/;

    //model.m_Material->m_Shader->bind();

    tinygltf::Model model;
    tinygltf::TinyGLTF gltf_ctx;
    std::string err;
    std::string warn;

    gltf_ctx.LoadBinaryFromFile(&model, &err, &warn, "assets/models/warbird.glb");

    if (!warn.empty()) {
        printf("Warn: %s\n", warn.c_str());
    }

    if (!err.empty()) {
        printf("Err: %s\n", err.c_str());
    }

    for (auto& mesh : model.meshes)
    {
        for (auto& primitive : mesh.primitives) 
        {
            const tinygltf::Accessor& accessor = model.accessors[primitive.attributes["POSITION"]];
            const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];

            const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];
            // bufferView byteoffset + accessor byteoffset tells you where the actual
            // position data is within the buffer. From there you should already know
            // how the data needs to be interpreted.
            std::cout << (unsigned)&buffer.data[bufferView.byteOffset + accessor.byteOffset] << '\n';

            const float* positions = reinterpret_cast<const float*>(&buffer.data[bufferView.byteOffset + accessor.byteOffset]);

            // From here, you choose what you wish to do with this position data. In
            // this case, we  will display it out.
            for (size_t i = 0; i < accessor.count; ++i)
            {
                vertices.push_back(dex::Vertex3D::Default(glm::vec3(positions[i * 3 + 0], positions[i * 3 + 1], positions[i * 3 + 2]), glm::vec3(0), glm::vec4(1)));
            } 
        }
    }

    for (size_t bv = 0; bv < model.bufferViews.size(); bv++)
    {
        if (model.bufferViews[bv].target == GL_ELEMENT_ARRAY_BUFFER)
        {
            const tinygltf::Buffer& buffer = model.buffers[model.bufferViews[bv].buffer];
            const tinygltf::Accessor& accessor = model.accessors[bv];
            
            if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
            {
                const uint16* bufferIndices = reinterpret_cast<const uint16*>(&buffer.data.at(0) + model.bufferViews[bv].byteOffset);

                for (size_t i = 0; i < accessor.count; i++)
                {
                    indices.emplace_back(bufferIndices[i]);
                }
            }
            else if (accessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
            {
                const uint32* bufferIndices = reinterpret_cast<const uint32*>(&buffer.data.at(0) + model.bufferViews[bv].byteOffset);

                for (size_t i = 0; i < accessor.count; i++)
                {
                    indices.emplace_back(bufferIndices[i]);
                }
            }
            else
            {
                std::cout << "Wrong Type\n";
                // Error
            }
        }
    }


    m_Entity.addComponent<dex::Component::Model>(dex::Mesh::Default3D(vertices, indices), mat);
    //auto& model = m_Entity.getComponent<dex::Component::Model>();
}

void SandBox::Shutdown()
{

}

void SandBox::update()
{
}

void SandBox::render()
{
    //auto& model = m_Player.getComponent<dex::Component::Model>();

    //model.m_Material->m_Shader->bind();

    ImGui::Begin("Test Window");

    static float rotX = 0.0f;
    static float rotY = 205.0f;
    static float rotZ = 350.0f;

    static float posX = 0.35f;
    static float posY = -0.5f;
    static float posZ = 2.4f;

    static float scale = 0.3f;

    static const float maxRot = 360;
    static const float maxPos = 5;

    ImGui::SliderFloat("Rotation X", &rotX, 0, maxRot);
    ImGui::SliderFloat("Rotation Y", &rotY, 0, maxRot);
    ImGui::SliderFloat("Rotation Z", &rotZ, 0, maxRot);
     
    ImGui::NewLine();

    ImGui::SliderFloat("Position X", &posX, -maxPos, maxPos);
    ImGui::SliderFloat("Position Y", &posY, -maxPos, maxPos);
    ImGui::SliderFloat("Position Z", &posZ, -maxPos, maxPos);

    ImGui::NewLine();

    ImGui::SliderFloat("Scale X", &scale, 0.1, 1.5);

    //static char buf[50];
    //ImGui::InputText("Text Input", buf, 50);

    auto& trans = m_Entity.getComponent<dex::Component::Transform>();

    trans.setPosition(glm::vec3(posX, posY, posZ));
    trans.setRotation(glm::vec3(rotX, rotY, rotZ));
    trans.setScale(glm::vec3(scale, scale, scale));
    //m_Entity.getComponent<dex::Component::Model>().m_Material->m_Shader->setModelMatrix(trans);

    //model.m_Mesh.render();

    Engine::renderer.renderScene(m_Scene);

    ImGui::End();

    //m_Texture.bind();
}
