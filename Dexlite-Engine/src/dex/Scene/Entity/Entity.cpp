#include "Entity.hpp"

dex::Entity::operator entt::entity() const { return m_Handle; }

bool dex::Entity::operator==(const Entity& other)
{
    return m_Handle == other.m_Handle && m_Scene == other.m_Scene;
}
