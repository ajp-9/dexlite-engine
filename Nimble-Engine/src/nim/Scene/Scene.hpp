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

		void doUpdate();
		void doPhysics();
		void doRender();
		template <typename T>
		void doCustumUpdate();
	private:
		entt::registry m_Registry;

		friend Entity;
	};

}
