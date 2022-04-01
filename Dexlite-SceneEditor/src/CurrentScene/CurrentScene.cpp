#include "CurrentScene.hpp"

#include <dex/Scene/Serializer/SceneSerializer.hpp>
#include <dex/Scene/Serializer/SceneDeserializer.hpp>

#include <bullet3/btBulletDynamicsCommon.h>

namespace dex
{
    CurrentScene::CurrentScene(dex::Window* window, dex::Renderer* renderer, dex::Physics* physics)
        : m_Window(window), m_Renderer(renderer), m_Physics(physics)
    {
		Scene = DeserializeScene("assets/scenes/testing0.json", renderer->ShaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D));


		setupEntities();
    }

	void CurrentScene::New()
	{
		Scene = dex::Scene();

		setupEntities();
	}

	void CurrentScene::Save()
	{
		SerializeScene(Path.u8string().c_str(), Scene);
	}
	
	void CurrentScene::SaveAs(const std::filesystem::path& path)
	{
		SerializeScene(path.u8string(), Scene);

		Path = path;
	}

	void CurrentScene::Open(const std::filesystem::path& path)
	{
		Scene = DeserializeScene(path.u8string(), m_Renderer->ShaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D));
		Path = path;
		setupEntities();
	}

    void CurrentScene::update(const float delta_time)
    {
		Scene.update();
		m_EditorRoot.updateChildrenTransform();

		auto lsph = Scene.getEntity("Light Sphere");

		//DEX_LOG_INFO(m_Physics->sbody->coll());
		m_Physics->sbody->getWorldTransform().getOrigin().getX();
		btTransform a;
		m_Physics->sbody->getMotionState()->getWorldTransform(a);
		//m_Physics->sbody->setActivationState(false);

		lsph.getComponent<Component::Transform>().setPosition(glm::vec3(a.getOrigin().getX(), a.getOrigin().getY(), a.getOrigin().getZ()));
		
		m_Physics->sbody->applyForce(btVector3(1, 0, 0), btVector3(0, 0, 0));
		
		

		const auto& mouse_delta = m_Window->Input.getMousePosChange() * (0.095 * static_cast<double>(delta_time));

		auto& cam_body_trans = ViewportCameraBody.getComponent<Component::Transform>();
		auto& cam_head_trans = ViewportCameraHead.getComponent<Component::Transform>();

		switch (CurrentViewportState)
		{
			case ViewportCameraState::NONE:
			{
				break;
			}
			case ViewportCameraState::FPS:
			{
				float32 speed = 1.5f * delta_time;

				if (m_Window->Input.getKeyState(dex::Event::Key::LEFT_SHIFT))
					speed = 7.5f * delta_time;

				if (m_Window->Input.getKeyState(dex::Event::Key::W))
					cam_body_trans.moveByLocal(glm::vec3(0, 0, speed));

				if (m_Window->Input.getKeyState(dex::Event::Key::S))
					cam_body_trans.moveByLocal(glm::vec3(0, 0, -speed));

				if (m_Window->Input.getKeyState(dex::Event::Key::A))
					cam_body_trans.moveByLocal(glm::vec3(-speed, 0, 0));

				if (m_Window->Input.getKeyState(dex::Event::Key::D))
					cam_body_trans.moveByLocal(glm::vec3(speed, 0, 0));

				if (m_Window->Input.getKeyState(dex::Event::Key::Q))
					cam_body_trans.moveByLocal(glm::vec3(0, -speed, 0));

				if (m_Window->Input.getKeyState(dex::Event::Key::E))
					cam_body_trans.moveByLocal(glm::vec3(0, speed, 0));

				cam_body_trans.rotateByEuler((glm::vec3(0, mouse_delta.x, 0)));

				float max_degrees = 90;

				if (cam_head_trans.getOrientationDegrees().x <= max_degrees && cam_head_trans.getOrientationDegrees().x >= -max_degrees)
					cam_head_trans.rotateByEulerLocal((glm::vec3(-mouse_delta.y, 0, 0)));
				if (cam_head_trans.getOrientationDegrees().x >= max_degrees)
					cam_head_trans.setOrientationEuler(glm::vec3(glm::radians(max_degrees), 0, 0));
				if (cam_head_trans.getOrientationDegrees().x <= -max_degrees)
					cam_head_trans.setOrientationEuler(glm::vec3(glm::radians(-max_degrees), 0, 0));

				break;
			}
			case ViewportCameraState::PAN:
			{
				float32 speed = 350.0f * delta_time;

				if (m_Window->Input.getKeyState(dex::Event::Key::LEFT_SHIFT))
					speed = 950.0f * delta_time;

				cam_body_trans.moveBy(-(cam_head_trans.getRight() * static_cast<float>(mouse_delta.x) * speed));
				cam_body_trans.moveBy(-(cam_head_trans.getUp() * static_cast<float>(mouse_delta.y) * speed));
				
				break;
			}
		}
    }

    void CurrentScene::render(const glm::vec2& viewport_size)
    {
		Scene.render(viewport_size, *m_Renderer, ViewportCameraHead);
    }

	void CurrentScene::setupEntities()
	{
		SelectedEntity = Entity(entt::null, &Scene);
		m_EditorRoot = Entity(&Scene, "dex::CurrentScene::m_EditorRoot", false);

		ViewportCameraBody = m_EditorRoot.addNewChild("dex::CurrentScene::m_ViewportCameraBody");
		ViewportCameraHead = ViewportCameraBody.addNewChild("dex::CurrentScene::m_ViewportCameraHead");

		auto& comp_camera = ViewportCameraHead.addComponent<Component::Camera>(false);

		comp_camera.setPerspective(65.0f, 0.01f, 500.0f);
	}
}
