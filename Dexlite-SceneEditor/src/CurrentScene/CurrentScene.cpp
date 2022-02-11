#include "CurrentScene.hpp"

#include <dex/Scene/Serializer/SceneSerializer.hpp>
#include <dex/Scene/Serializer/SceneDeserializer.hpp>

namespace dex
{
    CurrentScene::CurrentScene(dex::Window* window, dex::Renderer* renderer)
        : Window(window), Renderer(renderer)
    {
		m_ViewportCamera.addComponent<Component::Camera>(false);
		m_ViewportCamera.getComponent<Component::Camera>().setPerspective(65, 0.01, 1000);

		m_Head.addComponent<Component::Camera>(true);

		//m_Head.getComponent<Component::Camera>().setOrthographic(5, 0.001, 100);
		m_Head.getComponent<Component::Camera>().setPerspective(65, 0.01, 1000);

		//dex::Window->setCaptureMouse(true);

		//m_Warlock.addComponent<dex::Component::Model>("assets/models/spec_cube.glb", true);

		m_Warlock.addComponent<dex::Component::Model>(dex::LoadGLTF("assets/models/ruff_matrix.glb", renderer->ShaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D)));
		m_Warlock.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, 0, 10));
		//m_Warlock.getComponent<dex::Component::Transform>().setRotationEuler(glm::vec3(15, 0, 0));

		//m_Valdore.addComponent<dex::Component::Model>(dex::LoadGLTF("assets/models/warlock.glb", renderer->ShaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D)));
		m_Valdore.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, 0, -5));
		m_Valdore.getComponent<dex::Component::Transform>().setOrientationEuler(glm::vec3(0, glm::radians(180.0), 0));
		m_Valdore.getComponent<dex::Component::Transform>().setScale(glm::vec3(.5));

		m_Triangle.addComponent<dex::Component::Model>(dex::LoadGLTF("assets/models/plane.glb", renderer->ShaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D)));
		m_Triangle.getComponent<dex::Component::Transform>().setScale(glm::vec3(10, 10, 10));
		m_Triangle.getComponent<dex::Component::Transform>().setPosition(glm::vec3(0, -5, 0));

		m_XYZ.addComponent<dex::Component::Model>(dex::LoadGLTF("assets/models/xyz.glb", renderer->ShaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D)));
		m_XYZ.getComponent<dex::Component::Transform>().setPosition(glm::vec3(-7, 0, 3.5));
		m_XYZ.getComponent<dex::Component::Transform>().setScale(glm::vec3(.05));
		//m_XYZ.addComponent<dex::Component::Light::Directional>(true, glm::vec3(.8));

		m_LightSphere.addComponent<dex::Component::Model>(dex::LoadGLTF("assets/models/smooth_sphere.glb", renderer->ShaderManager.getShaderDerived<Shader::Default3D>(Shader::Type::DEFAULT_3D)));
		m_LightSphere.addComponent<dex::Component::Light::Ambient>(true, glm::vec3(.15));
		m_LightSphere.getComponent<dex::Component::Transform>().setPosition(glm::vec3(7, 0, 3));
		m_LightSphere.getComponent<dex::Component::Transform>().setScale(glm::vec3(.4));
		/////m_LightSphere.addComponent<dex::Component::Light::Point>(true, glm::vec3(1, 0, 0), 1.0, .5, .45);
		//m_Head.addComponent<dex::Component::Light::Directional>(true, glm::vec3(.8));

		////m_Head.addComponent<dex::Component::Light::Point>(true, glm::vec3(1, 0, 0), 1.0, .5, .45);

		m_LightSphere.addChild(m_XYZ);
		m_Player.addChild(m_Head);
		//m_Head.addComponent<dex::Component::Light::Point>(true, glm::vec3(1, 0, 0), 1.0, .5, .45);
		//m_Head.getComponent<dex::Component::Transform>().setScale(glm::vec3(1002, 133, 13223));

		SerializeScene("wat.txt", Scene);

 		Scene = DeserializeScene("wat.txt");

		DEX_LOG_INFO("{}", Scene.m_Root->isValid());
    }

    void CurrentScene::update(const float delta_time)
    {
		Scene.update();
		
		//m_LightSphere.getComponent<dex::Component::Transform>().rotateByEulerLocal(glm::vec3(glm::radians(.09), 0, 0));
		//m_LightSphere.getComponent<dex::Component::Transform>().rotateByEulerLocal(glm::vec3(0, -glm::radians(.09), 0));
		//m_LightSphere.getComponent<dex::Component::Transform>().rotateByEulerLocal(glm::vec3(0, 0, glm::radians(.09)));
		//m_Head.getComponent<dex::Component::Transform>().scaleByLocal(glm::vec3(1, 1, 1)); //fucks the camera

		//m_XYZ.getComponent<dex::Component::Transform>().moveBy(glm::vec3(0, 0, .001));

		auto& player_trans = m_Player.getComponent<dex::Component::Transform>();
		auto& head_trans = m_Head.getComponent<dex::Component::Transform>();

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
}
