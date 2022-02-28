#include "CurrentScene.hpp"

#include <dex/Scene/Serializer/SceneSerializer.hpp>
#include <dex/Scene/Serializer/SceneDeserializer.hpp>

namespace dex
{
    CurrentScene::CurrentScene(dex::Window* window, dex::Renderer* renderer)
        : m_Window(window), m_Renderer(renderer)
    {
		//Scene = DeserializeScene("assets/scenes/testing0.json", renderer->ShaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D));

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
		
		if (m_Window->isMouseCaptured())
		{
			auto& cam_body_trans = m_ViewportCameraBody.getComponent<Component::Transform>();
			auto& cam_head_trans = m_ViewportCameraHead.getComponent<Component::Transform>();

			float32 speed = .8f * delta_time;

			if (m_Window->Input.getKeyState(dex::Event::Key::LEFT_SHIFT))
				speed = 6 * delta_time;

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

			const auto& mouse_delta = m_Window->Input.getMousePosChange() * (0.095 * static_cast<double>(delta_time));

			cam_body_trans.rotateByEuler((glm::vec3(0, mouse_delta.x, 0)));

			float max_degrees = 90;

			if (cam_head_trans.getOrientationDegrees().x <= max_degrees && cam_head_trans.getOrientationDegrees().x >= -max_degrees)
				cam_head_trans.rotateByEulerLocal((glm::vec3(-mouse_delta.y, 0, 0)));
			if (cam_head_trans.getOrientationDegrees().x >= max_degrees)
				cam_head_trans.setOrientationEuler(glm::vec3(glm::radians(max_degrees), 0, 0));
			if (cam_head_trans.getOrientationDegrees().x <= -max_degrees)
				cam_head_trans.setOrientationEuler(glm::vec3(glm::radians(-max_degrees), 0, 0));
		}
    }

    void CurrentScene::render(const glm::vec2& viewport_size)
    {
		Scene.render(viewport_size, *m_Renderer, m_ViewportCameraHead);
    }

	void CurrentScene::setupEntities()
	{
		m_EditorRoot = Entity(&Scene, "dex::CurrentScene::m_EditorRoot", false);

		m_ViewportCameraBody = m_EditorRoot.addNewChild("dex::CurrentScene::m_ViewportCameraBody");
		m_ViewportCameraHead = m_ViewportCameraBody.addNewChild("dex::CurrentScene::m_ViewportCameraHead");

		auto& comp_camera = m_ViewportCameraHead.addComponent<Component::Camera>(false);

		comp_camera.setPerspective(65, 0.01, 1000);
	}
}
