#pragma once

#include <entt.hpp>

#include "Component/Camera/OrthographicCamComponent.hpp"
#include "Component/Camera/PerspectiveCamComponent.hpp"

namespace dex
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
		Component::OrthographicCamera* m_OrthoCamera = nullptr;
		Component::PerspectiveCamera* m_PerspCamera = nullptr;
		
		friend class Entity;
	};
}
