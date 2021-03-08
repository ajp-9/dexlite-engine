#pragma once

#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

class Window
{
public:
	Window(glm::ivec2 windowDimensions);
	~Window();

	void update();

	glm::ivec2 getDimensions();
private:
	void setupOpenGL();

private:
	SDL_Window* m_Window;
	SDL_GLContext m_GLContext;
};