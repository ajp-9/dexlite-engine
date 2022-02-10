#include "SceneSerializer.hpp"

#include <fstream>
#include <json.hpp>

#include "../Entity/Entity.hpp"

#include "../Component/TagComponent.hpp"
#include "../Component/Transform/TransformComponent.hpp"
#include "../Component/Camera/CameraComponent.hpp"
#include "../Component/ModelComponent.hpp"
#include "../Component/LightComponents.hpp"

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

    void SerializeScene(const std::string& file_location, const Scene& scene)
    {
        nlohmann::json json;

        for (const auto& entity : scene.m_Root->getChildren())
        {
            json["Entities"].emplace_back(SerializeEntity(entity));
        }

        std::ofstream(file_location) << json;
    }

    nlohmann::json SerializeEntity(const Entity& entity)
    {
        nlohmann::json json;

        //json[entity.getComponent<Component::Tag>().m_Tag];

        if (entity.hasComponent<Component::Tag>())
        {
            json["Components"].push_back(SerializeComponent<Component::Tag>(entity,
                [](const Component::Tag& tag) -> nlohmann::json
                {
                    nlohmann::json json;

                    json["Type"] = "Tag";

                    json["Data"]["m_Tag"] = tag.m_Tag;

                    return json;
                }
            ));
        }

        if (entity.hasComponent<Component::Transform>())
        {
            json["Components"].push_back(SerializeComponent<Component::Transform>(entity,
                [](const Component::Transform& transform) -> nlohmann::json
                {
                    nlohmann::json json;

                    json["Type"] = "Transform";

                    const auto& position = transform.getPosition();
                    json["Data"]["Position"] = { position.x, position.y, position.z };

                    const auto& orientation = transform.getOrientationQuat();
                    json["Data"]["Orientation"] = { orientation.w, orientation.x, orientation.y, orientation.z };

                    const auto& scale = transform.getScale();
                    json["Data"]["Scale"] = { scale.x, scale.y, scale.z };

                    return json;
                }
            ));
        }
        
        if (entity.hasComponent<Component::Camera>())
        {
            json["Components"].push_back(SerializeComponent<Component::Camera>(entity,
                [](const Component::Camera& camera) -> nlohmann::json
                {
                    nlohmann::json json;

                    json["Type"] = "Camera";

                    json["Data"]["Enabled"] = camera.IsEnabled;

                    if (camera.m_Type == Component::Camera::CameraType::ORTHOGRAPHIC)
                        json["Data"]["Projection"] = "Orthographic";
                    else if (camera.m_Type == Component::Camera::CameraType::PERSPECTIVE)
                        json["Data"]["Projection"] = "Perspective";
                    else
                        json["Data"]["Projection"] = "Unknown";

                    json["Data"]["OrthoSize"] = camera.m_Ortho_Size;

                    json["Data"]["Persp_FOV"] = camera.m_Persp_FOV;

                    json["Data"]["Near"] = camera.m_Near;
                    json["Data"]["Far"] = camera.m_Far;

                    json["Data"]["AspectRatio"] = camera.m_AspectRatio;

                    return json;
                }
            ));
        }

        if (entity.hasComponent<Component::Model>())
        {
            json["Components"].push_back(SerializeComponent<Component::Model>(entity,
                [](const Component::Model& model) -> nlohmann::json
                {
                    nlohmann::json json;

                    json["Type"] = "Model";

                    json["Data"]["Enabled"] = model.Enabled;
                    json["Data"]["FileLocation"] = model.FileLocation;

                    return json;
                }
            ));
        }

        if (entity.hasComponent<Component::Light::Ambient>())
        {
            json["Components"].push_back(SerializeComponent<Component::Light::Ambient>(entity,
                [](const Component::Light::Ambient& ambient) -> nlohmann::json
                {
                    nlohmann::json json;

                    json["Type"] = "AmbientLight";

                    json["Data"]["Enabled"] = ambient.Enabled;
                    json["Data"]["Color"] = { ambient.Color.x, ambient.Color.y, ambient.Color.z };

                    return json;
                }
            ));
        }

        if (entity.hasComponent<Component::Light::Directional>())
        {
            json["Components"].push_back(SerializeComponent<Component::Light::Directional>(entity,
                [](const Component::Light::Directional& directional) -> nlohmann::json
                {
                    nlohmann::json json;

                    json["Type"] = "DirectionalLight";

                    json["Data"]["Enabled"] = directional.Enabled;
                    json["Data"]["Color"] = { directional.Color.x, directional.Color.y, directional.Color.z };

                    return json;
                }
            ));
        }

        if (entity.hasComponent<Component::Light::Point>())
        {
            json["Components"].push_back(SerializeComponent<Component::Light::Point>(entity,
                [](const Component::Light::Point& point) -> nlohmann::json
                {
                    nlohmann::json json;

                    json["Type"] = "PointLight";

                    json["Data"]["Enabled"] = point.Enabled;
                    json["Data"]["Color"] = { point.Color.x, point.Color.y, point.Color.z };

                    return json;
                }
            ));
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
