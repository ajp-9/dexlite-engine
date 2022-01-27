#pragma once

#include <vector>
#include <GLFW/glfw3.h>

#include "../Event/KeyEvent.hpp"
#include "../Event/MouseEvent.hpp"

namespace dex
{
    class Input
    {
    public:
        void setWindowHandle(GLFWwindow* window_handle) { m_WindowHandle = window_handle; }

        // For the actual character movement
        bool getKeyState(Event::Key e);
        bool isKeyPressed(Event::Key e);
        bool isKeyReleased(Event::Key e);

        bool getAreKeyEventsHalted() { return m_AreKeyEventsHalted; }
        bool getAreMouseEventsHalted() { return m_AreMouseEventsHalted; }

        glm::dvec2 getMousePosition();
        glm::dvec2 getMousePosChange();

        // Returns actual mouse event, for stuff like position of mouse
        Event::MouseEvent getMousePressed(Event::MouseButton btn);
        // Returns actual mouse event, for stuff like position of mouse
        Event::MouseEvent getMouseReleased(Event::MouseButton btn);

        bool isMousePressed(Event::MouseButton btn);
        bool isMouseReleased(Event::MouseButton btn);

        void pollNewEvents();
        
        // Stops further events if you don't want them to propagate to the next layers.
        void stopEvents();
        // Stops further key events if you don't want them to propagate to the next layers.
        void stopKeyEvents();
        // Stops further mouse events if you don't want them to propagate to the next layers.
        void stopMouseEvents();

        void resetInput();
    private:
        void pushKeyEvent(Event::KeyEvent e);
        void pushMouseEvent(Event::MouseEvent e);
    private:
        GLFWwindow* m_WindowHandle = nullptr;

        std::vector<Event::KeyEvent> m_KeyEvents;
        std::vector<Event::MouseEvent> m_MouseEvents;

        bool m_AreKeyEventsHalted = false;
        bool m_AreMouseEventsHalted = false;
    public:
        friend class Window;
    };
}
