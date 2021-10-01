#pragma once

#include "Material.hpp"

namespace dex
{
    namespace Material
    {
        class Manager // reee materials are just values attached to specific shaders
        {
        public:
            Manager();

            void addMaterial(const std::shared_ptr<BaseNew>& shader);
            void removeMaterial(const std::string& name);

            std::shared_ptr<BaseNew>& getMaterial(const char* name);

            template <class T>
            inline std::shared_ptr<T> getMaterialDerived(const char* name)
            {
                return std::make_shared<T>(static_cast<T&>(*getMaterial(name)));
            }
        private:
            std::vector<std::shared_ptr<BaseNew>> m_Materials;
        };
    }
}
