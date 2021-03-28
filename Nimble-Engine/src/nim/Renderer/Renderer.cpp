#include "Renderer.hpp"

#include <glad/glad.h>

#include "ImGui/ImGuiAPI.hpp"

namespace nim
{
	void Renderer::Init(glm::uvec2 viewportDimensions)
	{
		setViewport(0, 0, viewportDimensions);

		glEnable(GL_DEPTH_TEST);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glClearColor(.0, .6, 0, 1.0f); // Clear the color buffer

		ImGuiAPI::Init();
	}

	void Renderer::Shutdown() 
	{
		ImGuiAPI::Shutdown();
	}

	void Renderer::update()
	{
		clear();
	}

	void Renderer::setViewport(uint32_t x, uint32_t y, glm::uvec2 dimensions)
	{
		glViewport(x, y, dimensions.x, dimensions.y);
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
