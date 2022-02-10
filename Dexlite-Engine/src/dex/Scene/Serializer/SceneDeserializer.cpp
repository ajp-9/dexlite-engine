#include "SceneDeserializer.hpp"

#include <fstream>
#include <json.hpp>

namespace dex
{
    //Entity 

    Scene DeserializeScene(const std::string& file_location)
    {
        //Scene scene;

        nlohmann::json json;
        json << std::ifstream(file_location);

        //return scene;
        return Scene();
    }
}
