#include "CurrentScene.hpp"

#include <dex/Scene/Serializer/SceneSerializer.hpp>
#include <dex/Scene/Serializer/SceneDeserializer.hpp>

namespace dex
{
    CurrentScene::CurrentScene(dex::Window* window, dex::Renderer* renderer)
        : Window(window), Renderer(renderer)
    {
		Scene = DeserializeScene("assets/scenes/testing0.json", renderer->ShaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D));

		resetViewportCamera();
    }

	void CurrentScene::New()
	{
		Scene = dex::Scene();

		resetViewportCamera();
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
		Scene = DeserializeScene(path.u8string(), Renderer->ShaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D));
		Path = path;
		resetViewportCamera();
	}

    void CurrentScene::update(const float delta_time)
    {
		Scene.update();
		
		//m_LightSphere.getComponent<dex::Component::Transform>().rotateByEulerLocal(glm::vec3(glm::radians(.09), 0, 0));
		//m_LightSphere.getComponent<dex::Component::Transform>().rotateByEulerLocal(glm::vec3(0, -glm::radians(.09), 0));
		//m_LightSphere.getComponent<dex::Component::Transform>().rotateByEulerLocal(glm::vec3(0, 0, glm::radians(.09)));
		//m_Head.getComponent<dex::Component::Transform>().scaleByLocal(glm::vec3(1, 1, 1)); //fucks the camera

		//m_XYZ.getComponent<dex::Component::Transform>().moveBy(glm::vec3(0, 0, .001));

		auto& player_trans = Scene.getEntity("Player").getComponent<Component::Transform>();

		//auto& player_trans = m_Player.getComponent<dex::Component::Transform>();
		//auto& head_trans = m_Head.getComponent<dex::Component::Transform>();

		//m_LightSphere.getComponent<dex::Component::Light::Point>().Position = player_trans.getWorldPosition();

		//player_trans.logAsInfo();

		float32 speed = .8 * delta_time;

		if (Window->Input.getKeyState(dex::Event::Key::LEFT_SHIFT))
			speed = 6 * delta_time;

		if (Window->Input.getKeyState(dex::Event::Key::W))
			player_trans.moveByLocal(glm::vec3(0, 0, speed));

		if (Window->Input.getKeyState(dex::Event::Key::S))
			player_trans.moveByLocal(glm::vec3(0, 0, -speed));

		if (Window->Input.getKeyState(dex::Event::Key::A))
			player_trans.moveByLocal(glm::vec3(-speed, 0, 0));

		if (Window->Input.getKeyState(dex::Event::Key::D))
			player_trans.moveByLocal(glm::vec3(speed, 0, 0));

		if (Window->Input.getKeyState(dex::Event::Key::Q))
			player_trans.moveByLocal(glm::vec3(0, -speed, 0));

		if (Window->Input.getKeyState(dex::Event::Key::E))
			player_trans.moveByLocal(glm::vec3(0, speed, 0));
    }

    void CurrentScene::render(const glm::vec2& viewport_size)
    {
		Scene.render(viewport_size, *Renderer);
    }

	void CurrentScene::resetViewportCamera()
	{
		m_ViewportCamera = Entity(&Scene, "dex::CurrentScene::m_ViewportCamera", false);

		auto& comp_camera = m_ViewportCamera.addComponent<Component::Camera>(false);

		comp_camera.setPerspective(65, 0.01, 1000);
	}
}
