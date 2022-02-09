#include "SceneSerializer.hpp"

#include <fstream>
#include <json.hpp>

#include "../Entity/Entity.hpp"

#include "../Component/TagComponent.hpp"
#include "../Component/Transform/TransformComponent.hpp"

namespace dex
{
    template <typename T>
    using SerializeComponentFunc = nlohmann::json(const T& t);

    nlohmann::json SerializeEntity(const Entity& entity);

    template <typename T>
    nlohmann::json SerializeComponent(const Entity& entity, SerializeComponentFunc<T>* func)
    {
        if (entity.hasComponent<T>())
            return func(entity.getComponent<T>());

        return nlohmann::json();
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

    Scene DeserializeScene(const std::string& file_location)
    {
        return Scene();
    }

    nlohmann::json SerializeEntity(const Entity& entity)
    {
        nlohmann::json json;

        //json[entity.getComponent<Component::Tag>().m_Tag];

        json["Components"].push_back(SerializeComponent<Component::Tag>(entity,
            [](const Component::Tag& tag) -> nlohmann::json
            {
                nlohmann::json json;

                json["Type"] = "Tag";

                json["Data"]["m_Tag"] = tag.m_Tag;

                return json;
            }
        ));
        
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
