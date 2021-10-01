#include "Input.hpp"

#include <GLFW/glfw3.h>

#include "../../Core/Engine.hpp"

namespace dex
{
    bool Input::getKeyState(Event::Key e)
    {
        return (!areKeyEventsHalted) && (glfwGetKey(dex::Engine::window.m_Window_GLFW, int32(e)) == GLFW_PRESS);
    }

    bool Input::isKeyPressed(Event::Key e)
    {
        if (!areKeyEventsHalted)
            for (auto& evnt : m_KeyEvents)
                if (evnt.m_Type == Event::Type::KEY_PRESS && evnt.m_KeyCode == e)
                    return true;

        return false;
    }

    bool Input::isKeyReleased(Event::Key e)
    {
        if (!areKeyEventsHalted)
            for (auto& evnt : m_KeyEvents)
                if (evnt.m_Type == Event::Type::KEY_RELEASE && evnt.m_KeyCode == e)
                    return true;

        return false;
    }

    glm::dvec2 Input::getMousePosition()
    {
        if (!areMouseEventsHalted)
        {
            glm::dvec2 tmp_pos;
            glfwGetCursorPos(Engine::window.m_Window_GLFW, &tmp_pos.x, &tmp_pos.y);
            return tmp_pos;
        }

        return glm::dvec2(0, 0);
    }

    glm::dvec2 Input::getMousePosChange()
    {
        if (!areMouseEventsHalted)
            for (auto& evnt : m_MouseEvents)
                if (evnt.m_Type == Event::Type::MOUSE && evnt.m_MouseType == Event::MouseType::MOVE)
                    return evnt.m_MousePosChange;

        return glm::dvec2(0, 0);
    }

    Event::MouseEvent Input::getMousePressed(Event::MouseButton btn)
    {
        if (!areMouseEventsHalted)
            for (auto& evnt : m_MouseEvents)
                if (evnt.m_Type == Event::Type::MOUSE && evnt.m_MouseType == Event::MouseType::BUTTON_PRESS && evnt.m_MouseButton == btn)
                    return evnt;

        return Event::MouseEvent(Event::Type::UNKNOWN, Event::MouseType::UNKNOWN, glm::dvec2(0), glm::dvec2(0), Event::MouseButton::UNKNOWN, 0);
    }

    Event::MouseEvent Input::getMouseReleased(Event::MouseButton btn)
    {
        if (!areMouseEventsHalted)
            for (auto& evnt : m_MouseEvents)
                if (evnt.m_Type == Event::Type::MOUSE && evnt.m_MouseType == Event::MouseType::BUTTON_RELEASE && evnt.m_MouseButton == btn)
                    return evnt;

        return Event::MouseEvent(Event::Type::UNKNOWN, Event::MouseType::UNKNOWN, glm::dvec2(0), glm::dvec2(0), Event::MouseButton::UNKNOWN, 0);
    }

    bool Input::isMousePressed(Event::MouseButton btn)
    {
        if (!areMouseEventsHalted)
            for (auto& evnt : m_MouseEvents)
                if (evnt.m_Type == Event::Type::MOUSE && evnt.m_MouseType == Event::MouseType::BUTTON_PRESS && evnt.m_MouseButton == btn)
                    return true;

        return false;
    }

    bool Input::isMouseReleased(Event::MouseButton btn)
    {
        if (!areMouseEventsHalted)
            for (auto& evnt : m_MouseEvents)
                if (evnt.m_Type == Event::Type::MOUSE && evnt.m_MouseType == Event::MouseType::BUTTON_RELEASE && evnt.m_MouseButton == btn)
                    return true;

        return false;
    }

    void Input::stopEvents()
    {
        areKeyEventsHalted = true;
        areMouseEventsHalted = true;
    }

    void Input::stopKeyEvents()
    {
        areKeyEventsHalted = true;
    }

    void Input::stopMouseEvents()
    {
        areMouseEventsHalted = true;
    }

    void Input::pushKeyEvent(Event::KeyEvent e)
    {
        m_KeyEvents.emplace_back(e);
    }

    void Input::pushMouseEvent(Event::MouseEvent e)
    {
        m_MouseEvents.emplace_back(e);
    }

    void Input::resetInput()
    {
        areKeyEventsHalted = false;
        m_KeyEvents.clear();
        areMouseEventsHalted = false;
        m_MouseEvents.clear();
    }
}
