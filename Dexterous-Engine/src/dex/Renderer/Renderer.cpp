#include "Renderer.hpp"

#include <glad/glad.h>

namespace dex
{
	Renderer::Renderer(glm::uvec4 viewport)
	{
		glEnable(GL_DEPTH_TEST);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		glClearColor(.1, .1, .1, 1.0f); // Clear the color buffer
	}

	Renderer::~Renderer() 
	{

	}

	void Renderer::beginFrame()
	{
		m_ImGuiAPI.beginFrame();
	}

	void Renderer::endFrame()
	{
		m_ImGuiAPI.endFrame();
	}

	void Renderer::update() {}

	void Renderer::renderScene(Scene& scene)
	{
		scene.render();
	}

	void Renderer::setViewportSize(glm::uvec2 size)
	{
		m_Viewport = glm::uvec4(m_Viewport.x, m_Viewport.y, size.x, size.y);
		glViewport(m_Viewport.x, m_Viewport.y, size.x, size.y);
	}

	void Renderer::setViewportPosition(glm::uvec2 position)
	{
		m_Viewport = glm::uvec4(position.x, position.y, m_Viewport.z, m_Viewport.w);
		glViewport(position.x, position.y, m_Viewport.x, m_Viewport.y);
	}

	void Renderer::setClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
