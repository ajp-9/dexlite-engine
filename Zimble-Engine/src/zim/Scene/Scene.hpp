#pragma once

#include <entt.hpp>

#include "Component/Camera/OrthoCamera.hpp"
#include "Component/Camera/PerspCamera.hpp"

namespace zim
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity createEntity();
		void destroyEntity(Entity entity);

		void findSetMainCamera();

		void update();
		void physics();
		void render();
		template <typename T>
		void doCustumUpdate() {}
	private:
		entt::registry m_Registry;
		Component::OrthoCamera* m_OrthoCamera = nullptr;
		Component::PerspCamera* m_PerspCamera = nullptr;
		
		friend class Entity;
	};
}
