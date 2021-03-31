#pragma once

#include <iostream>

#include "../Scene.hpp"

namespace nim
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene) : m_Handle(handle), m_Scene(scene) {}

		template<typename T, typename... Args>
		inline T& addComponent(Args&&... args)
		{
			if (!hasComponent<T>())
			{
				if (m_Scene != nullptr)
					return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
			}
			else
			{
				std::cout << "WARNING: Entity already has that component!\n";
			}

			static T t; return t;
		}

		template <typename T>
		inline void removeComponent()
		{
			m_Scene->m_Registry.remove<T>(m_Handle);
		}

		template <typename T>
		inline T& getComponent()
		{
			return m_Scene->m_Registry.get<T>(m_Handle);
		}

		template <typename T>
		inline bool hasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_Handle);
		}

		operator entt::entity() const;
		bool operator==(const Entity& other);
	private:
		entt::entity m_Handle;
		Scene* m_Scene = nullptr;
	};
}
