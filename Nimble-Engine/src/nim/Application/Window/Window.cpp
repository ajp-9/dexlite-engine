#include "Window.hpp"

#include <glad/glad.h>
#include <iostream>

#include "../Layer/Event/KeyCodes.hpp"
#include "../Layer/Event/KeyEvent.hpp"

namespace nim
{
    Window::Window(glm::ivec2 windowDimensions)
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

        m_GLContext = SDL_GL_CreateContext(m_Window);
        if (m_GLContext == NULL)
            fprintf(stderr, "%s: %s\n", "Could not create the OpenGL context: ", SDL_GetError());

        // Load OpenGL functions glad SDL
        gladLoadGLLoader(SDL_GL_GetProcAddress);

        SDL_UpdateWindowSurface(m_Window);

        setupOpenGL();
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

        glClearColor(.0, .4, 0, 1.0f); // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    glm::ivec2 Window::getDimensions()
    {
        glm::ivec2 dimensions;
        SDL_GetWindowSize(m_Window, &dimensions.x, &dimensions.y);
        return dimensions;
    }

    std::vector<std::unique_ptr<event::Event>> Window::getEventQueue()
    {
        std::vector<std::unique_ptr<event::Event>> events;

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_KEYDOWN:
                events.emplace_back(std::make_unique<event::KeyEvent>(event::type::KEY_DOWN, e.key.keysym.scancode));
                break;
            case SDL_KEYUP:
                events.emplace_back(std::make_unique<event::KeyEvent>(event::type::KEY_UP, e.key.keysym.scancode));
                break;
            default:
                break;
            }
        }

        const Uint8* k = SDL_GetKeyboardState(NULL);

        for (uint16_t i = 0; i < event::key::MAX_KEY; i++)
            if (k[i])
                events.emplace_back(std::make_unique<event::KeyEvent>(event::type::KEYBOARD, i));
                //std::cout << i << std::endl;

        return events;
    }

    void Window::setupOpenGL()
    {
        glm::ivec2 drawableSize;
        SDL_GL_GetDrawableSize(m_Window, &drawableSize.x, &drawableSize.y);
        glViewport(0, 0, drawableSize.x, drawableSize.y);
        glEnable(GL_DEPTH_TEST);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
}
