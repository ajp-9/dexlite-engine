#include "Entity.hpp"

nim::Entity::operator entt::entity() const { return m_Handle; }

bool nim::Entity::operator==(const Entity& other)
{
	return m_Handle == other.m_Handle && m_Scene == other.m_Scene;
}

