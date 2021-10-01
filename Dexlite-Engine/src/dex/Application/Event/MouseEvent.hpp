#pragma once

#include <glm/vec2.hpp>

#include "EventBase.hpp"

namespace dex
{
    namespace Event
    {
        enum class MouseType : uint32
        {
            UNKNOWN,
            MOVE,
            BUTTON_PRESS,
            BUTTON_RELEASE,
            SCROLL_UP,
            SCROLL_DOWN
        };

        enum class MouseButton : uint32
        {
            UNKNOWN,
            LEFT,
            MIDDLE,
            RIGHT
        };

        struct MouseEvent : Base
        {
            MouseEvent(Type type, MouseType mouseType, glm::dvec2 mousePosition, glm::dvec2 mousePosChange, MouseButton mouseButton, uint32_t scrollAmount)
                : Base(type), m_MouseType(mouseType), m_MousePosition(mousePosition), m_MousePosChange(mousePosChange), m_MouseButton(mouseButton), m_ScrollAmount(scrollAmount)
            {}

            /*operator bool()
            {
                if (m_MouseType == MouseType::BUTTON_PRESS || m_MouseType == MouseType::BUTTON_RELEASE)
                    return true;
            }*/

            MouseType m_MouseType;
            glm::dvec2 m_MousePosition;
            glm::dvec2 m_MousePosChange;
            MouseButton m_MouseButton;
            uint32_t m_ScrollAmount;
        };
    }
}
