#include "SceneDeserializer.hpp"

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
    Entity DeserializeEntity(const nlohmann::json& json, Scene* scene, Entity& parent)
    {
        Entity entity = parent.addNewChild();
        
        if (!json["Components"]["Tag"].is_null())
            entity.getComponent<Component::Tag>().m_Tag = json["Components"]["Tag"]["String"];
            
        if (!json["Components"]["Transform"].is_null())
        {
            auto& transform = entity.getComponent<Component::Transform>();

            auto& pos_json = json["Components"]["Transform"]["Position"];
            transform.setPosition(glm::vec3(pos_json[0], pos_json[1], pos_json[2]));

            auto& orient_json = json["Components"]["Transform"]["Orientation"];
            transform.setOrientationQuat(glm::quat(orient_json[0], orient_json[1], orient_json[2], orient_json[3]));

            auto& scale_json = json["Components"]["Transform"]["Scale"];
            transform.setPosition(glm::vec3(scale_json[0], scale_json[1], scale_json[2]));
        }


        return entity;
    }

    Scene DeserializeScene(const std::string& file_location)
    {
        Scene scene;
        
        nlohmann::json json;
        json << std::ifstream(file_location);

        for (auto& entity_json : json["Entities"])
        {
            DeserializeEntity(entity_json, &scene, *scene.m_Root);
        }

        return scene;
    }
}
