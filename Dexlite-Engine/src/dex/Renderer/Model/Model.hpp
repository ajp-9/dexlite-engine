#pragma once

#include "../Mesh/Mesh.hpp"
#include "../Material/3D/MaterialDefault3D.hpp"

namespace dex
{
    struct Model
    {
        Model() = default;
        Model(Mesh::Default3D&& mesh, std::shared_ptr<Material::Default3D> material, const std::string& file_location)
            : Mesh(std::move(mesh)), Material(material), FileLocation(file_location)
        {}
        ~Model() = default;

        //Model(const Model& other) = delete;
        //const Model& operator=(const Model& other) = delete;

        Model(Model&& other) noexcept
            : Mesh(std::move(other.Mesh)), Material(other.Material), FileLocation(other.FileLocation)
        {}
        Model& operator=(Model&& other) noexcept
        {
            if (this != &other)
            {
                Mesh = std::move(other.Mesh);
                Material = other.Material;
                FileLocation = other.FileLocation;
            }

            return *this;
        }
    public:
        Mesh::Default3D Mesh;
        std::shared_ptr<Material::Default3D> Material = nullptr;

        std::string FileLocation;
    };
}
