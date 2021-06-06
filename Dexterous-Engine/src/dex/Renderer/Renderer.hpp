#pragma once

#include <glm/vec4.hpp>
#include "../Scene/Scene.hpp"
#include "Shader/ShaderManager.hpp"

namespace dex
{
	class Renderer
	{
		static void Init(glm::uvec4 viewport);
		static void Shutdown();

		static void beginFrame();
		static void endFrame();

		static void update();
		static void renderScene(Scene& scene);

		static void setViewportSize(glm::uvec2 size);
		static void setViewportPosition(glm::uvec2 position);

		static void setClearColor(const glm::vec4& color);
		static void clear();

	public:
		static Shader::Manager s_ShaderManager;
	private:
		/*// x, y = position of viewport
		// z, w = dimensions of viewport
		static glm::uvec4 s_LastViewport;*/

		static glm::uvec4 s_Viewport;

		friend class Engine;
		friend class Application;
		friend class Window;
	};
}
