#include "SceneDeserializer.hpp"

#include <fstream>
#include <sstream>
#include <json.hpp>

#include "../Entity/Entity.hpp"

#include "../../Renderer/Model/LoadGLTF.hpp"

#include "../Component/TagComponent.hpp"
#include "../Component/Transform/TransformComponent.hpp"
#include "../Component/Camera/CameraComponent.hpp"
#include "../Component/ModelComponent.hpp"
#include "../Component/LightComponents.hpp"
#include "../Components.hpp"

namespace dex
{
    Entity DeserializeEntity(const nlohmann::json& json, Scene* scene, Physics* physics, const std::shared_ptr<Shader::Default3D>& shader_default_3d)
    {
        Entity entity = { scene };
        
        if (json["Components"].find("Tag") != json["Components"].end())
            entity.getComponent<Component::Tag>().m_Tag = json["Components"]["Tag"]["String"];
            
        if (json["Components"].find("Transform") != json["Components"].end())
        {
            auto& transform = entity.getComponent<Component::Transform>();

            auto& pos_json = json["Components"]["Transform"]["Position"];
            transform.setPosition(glm::vec3(pos_json[0], pos_json[1], pos_json[2]));

            auto& orient_json = json["Components"]["Transform"]["Orientation"];
            transform.setOrientationQuat(glm::quat(orient_json[0], orient_json[1], orient_json[2], orient_json[3]));

            auto& scale_json = json["Components"]["Transform"]["Scale"];
            transform.setScale(glm::vec3(scale_json[0], scale_json[1], scale_json[2]));
        }

        if (json["Components"].find("Camera") != json["Components"].end())
        {
            nlohmann::json camera_json = json["Components"]["Camera"];
            auto& camera = entity.addComponent<Component::Camera>();

            camera.IsEnabled = camera_json["Enabled"];
            
            if (camera_json["Projection"] == "Orthographic")
                camera.m_Type = Component::Camera::CameraType::ORTHOGRAPHIC;
            if (camera_json["Projection"] == "Perspective")
                camera.m_Type = Component::Camera::CameraType::PERSPECTIVE;

            camera.m_Ortho_Size = camera_json["OrthoSize"];

            camera.m_Persp_FOV = camera_json["Persp_FOV"];

            camera.m_Near = camera_json["Near"];
            camera.m_Far = camera_json["Far"];

            camera.m_AspectRatio = camera_json["AspectRatio"];
        }

        if (json["Components"].find("Model") != json["Components"].end())
        {
            nlohmann::json model_json = json["Components"]["Model"];
            auto& model = entity.addComponent<Component::Model>();

            std::ofstream("loctest.txt") << std::string(model_json["FileLocation"]);

            model = LoadGLTF(std::string(model_json["FileLocation"]), shader_default_3d);

            model.Enabled = model_json["Enabled"];
            model.FileLocation = std::filesystem::path(std::string(model_json["FileLocation"]));
        }

        if (json["Components"].find("AmbientLight") != json["Components"].end())
        {
            nlohmann::json ambient_json = json["Components"]["AmbientLight"];
            auto& ambient = entity.addComponent<Component::Light::Ambient>();

            ambient.Enabled = ambient_json["Enabled"];

            auto& pos_json = ambient_json["Color"];
            ambient.Color = glm::vec3(pos_json[0], pos_json[1], pos_json[2]);
        }

        if (json["Components"].find("DirectionalLight") != json["Components"].end())
        {
            nlohmann::json directional_json = json["Components"]["DirectionalLight"];
            auto& directional = entity.addComponent<Component::Light::Directional>();

            directional.Enabled = directional_json["Enabled"];

            auto& pos_json = directional_json["Color"];
            directional.Color = glm::vec3(pos_json[0], pos_json[1], pos_json[2]);
        }

        if (json["Components"].find("PointLight") != json["Components"].end())
        {
            nlohmann::json point_json = json["Components"]["PointLight"];
            auto& point = entity.addComponent<Component::Light::Point>();

            point.Enabled = point_json["Enabled"];

            auto& pos_json = point_json["Color"];
            point.Color = glm::vec3(pos_json[0], pos_json[1], pos_json[2]);
        }
        
        if (json["Components"].find("RigidBody") != json["Components"].end())
        {
            nlohmann::json body_json = json["Components"]["RigidBody"];

            RigidBodyType body_type;
            std::string body_type_str = body_json["Type"];

            if (body_type_str == "Static")
                body_type = RigidBodyType::STATIC;
            else if (body_type_str == "Kinematic")
                body_type = RigidBodyType::KINEMATIC;
            else if (body_type_str == "Dynamic")
                body_type = RigidBodyType::DYNAMIC;

            std::shared_ptr<CollisionShape> collision_shape;
            std::string shape_type = body_json["CollisionShape"];

            if (shape_type == "None")
                collision_shape = std::make_shared<CollisionShape>();
            else if (shape_type == "Sphere")
                collision_shape = std::make_shared<SphereCollisionShape>(body_json["CollisionShape"]["Radius"]);
            else if (shape_type == "Box")
            {
                nlohmann::json json_extents = body_json["CollisionShape"]["HalfExtents"];
                glm::vec3 half_extents = { json_extents[0], json_extents[1], json_extents[2] };
                collision_shape = std::make_shared<BoxCollisionShape>(half_extents);
            }
            else if (shape_type == "ConvexHull")
            {
                if (entity.hasComponent<Component::Model>())
                    collision_shape = std::make_shared<ConvexHullCollisionShape>(entity.getComponent<Component::Model>().Mesh, entity.getComponent<Component::Transform>().getScale());
            }
            else if (shape_type == "TriangleMesh")
            {
                if (entity.hasComponent<Component::Model>())
                    collision_shape = std::make_shared<TriangleMeshCollisionShape>(entity.getComponent<Component::Model>().Mesh, entity.getComponent<Component::Transform>().getScale());
            }

            float mass = json["Components"]["RigidBody"]["Mass"];

            auto& rigid_body = entity.addComponent<Component::RigidBody>(
                physics->createRigidbody(
                    body_type,
                    collision_shape,
                    mass,
                    entity.getComponent<Component::Transform>().getBasicTransform()));
        }

        if (json.find("Children") != json.end())
            for (const auto& child : json["Children"])
                entity.addChild(DeserializeEntity(child, scene, physics, shader_default_3d));

        return entity;
    }

    Scene DeserializeScene(const std::filesystem::path& file_location, Renderer* renderer, Physics* physics, const std::shared_ptr<Shader::Default3D>& shader_default_3d)
    {
        Scene scene = { renderer, physics };
        nlohmann::json json;

        try
        {
            std::stringstream str_stream;
            str_stream << std::ifstream(file_location).rdbuf();
            json = json.parse(str_stream.str());
        }
        catch (const std::exception& exception)
        {
            DEX_LOG_ERROR("dex::SerializeScene(): {}", exception.what());
        }

        for (auto& entity_json : json["Entities"])
        {
            DeserializeEntity(entity_json, &scene, physics, shader_default_3d);
        }

        return scene;
    }
}
