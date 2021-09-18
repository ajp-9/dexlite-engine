#include "MaterialManager.hpp"

#include "3D/MaterialDefault3D.hpp"

namespace dex
{
    namespace Material
    {
        Manager::Manager()
        {
            //addMaterial(std::make_shared<Default3D>());
        }
         
        void Manager::addMaterial(const std::shared_ptr<BaseNew>& shader)
        {
            m_Materials.emplace_back(shader);
        }

        void Manager::removeMaterial(const std::string& name)
        {
            for (uint32 i = 0; i < m_Materials.size(); i++)
                if (m_Materials.at(i)->m_Name == name)
                    m_Materials.erase(m_Materials.begin() + i);
        }

        std::shared_ptr<BaseNew>& Manager::getMaterial(const char* name)
        {
            for (auto& material : m_Materials)
                if (material->m_Name == name)
                    return material;
        }
    }
}
