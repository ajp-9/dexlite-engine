#include "SceneSerializer.hpp"

#include <fstream>
#include <json.hpp>

#include "../Entity/Entity.hpp"

#include "../Component/TagComponent.hpp"
#include "../Component/Transform/TransformComponent.hpp"
#include "../Component/Camera/CameraComponent.hpp"
#include "../Component/ModelComponent.hpp"
#include "../Component/LightComponents.hpp"
#include "../Components.hpp"

namespace dex
{
    template <typename T>
    using SerializeComponentFunc = nlohmann::json(const T& t);

    nlohmann::json SerializeEntity(const Entity& entity);

    template <typename T>
    nlohmann::json SerializeComponent(const Entity& entity, SerializeComponentFunc<T>* func)
    {
        return func(entity.getComponent<T>());
    }

    void SerializeScene(const std::filesystem::path& file_location, const Scene& scene)
    {
        nlohmann::json json;

        for (const auto& entity : scene.Root->getChildren())
        {
            json["Entities"].emplace_back(SerializeEntity(entity)); 
        }

        try
        {
            if (std::filesystem::path(file_location).has_filename())
            {
                if (!std::filesystem::exists(file_location.parent_path()))
                    if (!file_location.parent_path().empty())
                        std::filesystem::create_directory(file_location.parent_path());

                std::ofstream(file_location) << json;
            }
        }
        catch (const std::exception& exception)
        {
            DEX_LOG_ERROR("dex::SerializeScene(): {}", exception.what());
        }
    }

    nlohmann::json SerializeEntity(const Entity& entity)
    {
        nlohmann::json json;

        if (entity.hasComponent<Component::Tag>())
        {
            json["Components"]["Tag"] = SerializeComponent<Component::Tag>(entity,
                [](const Component::Tag& tag) -> nlohmann::json
                {
                    nlohmann::json json;

                    json["String"] = tag.m_Tag;

                    return json;
                }
            );
        }

        if (entity.hasComponent<Component::Transform>())
        {
            json["Components"]["Transform"] = SerializeComponent<Component::Transform>(entity,
                [](const Component::Transform& transform) -> nlohmann::json
                {
                    nlohmann::json json;

                    const auto& position = transform.getPosition();
                    json["Position"] = { position.x, position.y, position.z };

                    const auto& orientation = transform.getOrientationQuat();
                    json["Orientation"] = { orientation.w, orientation.x, orientation.y, orientation.z };

                    const auto& scale = transform.getScale();
                    json["Scale"] = { scale.x, scale.y, scale.z };

                    return json;
                }
            );
        }
        
        if (entity.hasComponent<Component::Camera>())
        {
            json["Components"]["Camera"] = SerializeComponent<Component::Camera>(entity,
                [](const Component::Camera& camera) -> nlohmann::json
                {
                    nlohmann::json json;

                    json["Enabled"] = camera.IsEnabled;

                    if (camera.m_Type == Component::Camera::CameraType::ORTHOGRAPHIC)
                        json["Projection"] = "Orthographic";
                    else if (camera.m_Type == Component::Camera::CameraType::PERSPECTIVE)
                        json["Projection"] = "Perspective";

                    json["OrthoSize"] = camera.m_Ortho_Size;

                    json["Persp_FOV"] = camera.m_Persp_FOV;

                    json["Near"] = camera.m_Near;
                    json["Far"] = camera.m_Far;

                    json["AspectRatio"] = camera.m_AspectRatio;

                    return json;
                }
            );
        }

        if (entity.hasComponent<Component::Model>())
        {
            json["Components"]["Model"] = SerializeComponent<Component::Model>(entity,
                [](const Component::Model& model) -> nlohmann::json
                {
                    nlohmann::json json;

                    json["Enabled"] = model.Enabled;
                    json["FileLocation"] = model.FileLocation.generic_u8string(); // When serializing stuff it will needs to be cross-compatible.

                    return json;
                }
            );
        }

        if (entity.hasComponent<Component::Light::Ambient>())
        {
            json["Components"]["AmbientLight"] = SerializeComponent<Component::Light::Ambient>(entity,
                [](const Component::Light::Ambient& ambient) -> nlohmann::json
                {
                    nlohmann::json json;

                    json["Enabled"] = ambient.Enabled;
                    json["Color"] = { ambient.Color.x, ambient.Color.y, ambient.Color.z };

                    return json;
                }
            );
        }

        if (entity.hasComponent<Component::Light::Directional>())
        {
            json["Components"]["DirectionalLight"] = SerializeComponent<Component::Light::Directional>(entity,
                [](const Component::Light::Directional& directional) -> nlohmann::json
                {
                    nlohmann::json json;

                    json["Type"] = "DirectionalLight";

                    json["Enabled"] = directional.Enabled;
                    json["Color"] = { directional.Color.x, directional.Color.y, directional.Color.z };

                    return json;
                }
            );
        }

        if (entity.hasComponent<Component::Light::Point>())
        {
            json["Components"]["PointLight"] = SerializeComponent<Component::Light::Point>(entity,
                [](const Component::Light::Point& point) -> nlohmann::json
                {
                    nlohmann::json json;

                    json["Type"] = "PointLight";

                    json["Enabled"] = point.Enabled;
                    json["Color"] = { point.Color.x, point.Color.y, point.Color.z };

                    return json;
                }
            );
        }
        
        if (entity.hasComponent<Component::RigidBody>())
        {
            json["Components"]["RigidBody"] = SerializeComponent<Component::RigidBody>(entity,
                [](const Component::RigidBody& rigid_body) -> nlohmann::json
                {
                    nlohmann::json json;

                    if (rigid_body.Type == RigidBodyType::STATIC)
                        json["Type"] = "Static";
                    else if (rigid_body.Type == RigidBodyType::KINEMATIC)
                        json["Type"] = "Kinematic";
                    else if (rigid_body.Type == RigidBodyType::DYNAMIC)
                        json["Type"] = "Dynamic";

                    json["Mass"] = rigid_body.getMass();

                    json["CollisionShape"] = rigid_body.CollisionShape->Type;

                    switch (rigid_body.CollisionShape->Type)
                    {
                        case CollisionShapeType::NONE:
                            json["CollisionShape"] = "None";
                            break;
                        case CollisionShapeType::SPHERE:
                            json["CollisionShape"] = "Sphere";
                            json["CollisionShape"]["Radius"] = static_cast<SphereCollisionShape*>(rigid_body.CollisionShape.get())->Radius;
                            break;
                        case CollisionShapeType::BOX:
                        {
                            json["CollisionShape"] = "Box";
                            const auto& half_extents = static_cast<BoxCollisionShape*>(rigid_body.CollisionShape.get())->HalfExtents;
                            json["CollisionShape"]["HalfExtents"] = { half_extents.x, half_extents.y, half_extents.z };
                            break;
                        }
                        case CollisionShapeType::CONVEX_HULL:
                            json["CollisionShape"] = "ConvexHull";
                            break;
                        case CollisionShapeType::TRIANGLE_MESH:
                            json["CollisionShape"] = "TriangleMesh";
                            break;
                    }

                    return json;
                }
            );
        }

        for (const auto& child: entity.getChildren())
        {
            json["Children"].emplace_back(SerializeEntity(child));
        }

        return json;
    }

    template<typename T>
    nlohmann::json SerializeComponent(const Entity& entity)
    {
        return nlohmann::json();
    }
}
