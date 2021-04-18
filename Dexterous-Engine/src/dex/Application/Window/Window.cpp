#include "Window.hpp"

#include <glad/glad.h>
#include <iostream>
#include <glm/vec2.hpp>

#include "../../Renderer/Renderer.hpp"

namespace dex
{
    Window::Window(glm::uvec2 windowDimensions)
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        {
            std::cout << "Failed to initialize the SDL2 library\n";
        }

        m_Window = SDL_CreateWindow(
            "Game",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowDimensions.x, windowDimensions.y,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

        if (!m_Window)
            fprintf(stderr, "%s: %s\n", "Couldn't create window: ", SDL_GetError());

        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // allocate 2 buffers
        //SDL_GL_SetSwapInterval(1); // vsync

        m_GLContext = SDL_GL_CreateContext(m_Window);
        if (m_GLContext == NULL)
            fprintf(stderr, "%s: %s\n", "Could not create the OpenGL context: ", SDL_GetError());

        // Load OpenGL functions glad SDL
        gladLoadGLLoader(SDL_GL_GetProcAddress);

        SDL_UpdateWindowSurface(m_Window);
    }

    Window::~Window()
    {
        SDL_GL_DeleteContext(m_GLContext);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }

    void Window::update()
    {
        SDL_GL_SwapWindow(m_Window); // swap buffers
    }

    glm::ivec2 Window::getDimensions()
    {
        glm::ivec2 dimensions;
        SDL_GetWindowSize(m_Window, &dimensions.x, &dimensions.y);
        return dimensions;
    }
}
