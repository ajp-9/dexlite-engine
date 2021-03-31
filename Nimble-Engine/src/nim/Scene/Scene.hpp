#pragma once

#include <entt.hpp>

namespace nim
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity createEntity();
		void destroyEntity(Entity entity);

		void update();
		void physics();
		void render();
		template <typename T>
		void doCustumUpdate() {}
	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}
