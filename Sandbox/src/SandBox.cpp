#include "SandBox.hpp"

#include "Layers/WorldLayer.hpp"

#include <entt.hpp>

#include <iostream>

#include <dex/Scene/Component/TransformComponent.hpp>
#include "Layers/DebugLayer.hpp"
#include <imgui/imgui.h>
#include <dex/Scene/Component/ModelComponent.hpp>

#include <tiny_obj_loader.h>

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

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, "assets/models/ship.obj", "assets/models/", true);

    size_t index_offset = 0;

    for (size_t f = 0; f < shapes[0].mesh.num_face_vertices.size(); f++)
    {
        unsigned char num_face_verts = shapes[0].mesh.num_face_vertices[f];

        for (unsigned char v = 0; v < num_face_verts; v++)
        {
            tinyobj::index_t index = shapes[0].mesh.indices[index_offset + v];

            float vx = attrib.vertices[(size_t)index.vertex_index * 3 + 0];
            float vy = attrib.vertices[(size_t)index.vertex_index * 3 + 1];
            float vz = attrib.vertices[(size_t)index.vertex_index * 3 + 2];
            
            float tx = attrib.texcoords[(size_t)index.texcoord_index * 2 + 0];
            float ty = attrib.texcoords[(size_t)index.texcoord_index * 2 + 1];
            
            float nx = attrib.normals[(size_t)index.normal_index * 3 + 0];
            float ny = attrib.normals[(size_t)index.normal_index * 3 + 1];
            float nz = attrib.normals[(size_t)index.normal_index * 3 + 2];

            dex::Vertex3D::Default vertex(glm::vec3(vx, vy, vz), glm::vec3(nx, ny, nz), glm::vec4(1), glm::vec2(tx, ty));

            vertices.push_back(vertex);

            indices.push_back((uint32)index_offset + v);
        }

        index_offset += num_face_verts;
    }

    m_Entity.addComponent<dex::Component::Model>(dex::Mesh::Default3D(vertices, indices), mat);
    auto& model = m_Entity.getComponent<dex::Component::Model>();
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
