#pragma once

#include "../Mesh/Mesh.hpp"
#include "../Material/3D/MaterialDefault3D.hpp"

namespace dex
{
    struct Model
    {
        Model() = default;
        Model(Mesh::Default3D&& mesh, std::shared_ptr<Material::Default3D> material)
            : Mesh(std::move(mesh)), Material(material)
        {}

        Model(const Model& other) = delete;
        const Model& operator=(const Model& other) = delete;

        Model(Model&& other) noexcept
            : Mesh(std::move(other.Mesh)), Material(other.Material)
        {}
        Model& operator=(Model&& other) noexcept
        {
            if (this != &other)
            {
                Mesh = std::move(other.Mesh);
                Material = other.Material;
            }

            return *this;
        }

        Mesh::Default3D Mesh;
        std::shared_ptr<Material::Default3D> Material = nullptr;
    };
}
