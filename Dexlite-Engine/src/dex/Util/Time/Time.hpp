#pragma once

#include <chrono>

#include "../Typedefs.hpp"

namespace dex
{
    class Time
    {
    public:
        Time(int fps = 60, bool sleepInstead = false)
            : m_FPS(fps), m_SleepInstead(sleepInstead)
        {}

        void doCycle();

        void sleep();
        float32 getDeltaTime() { return m_DeltaTime; }
        float32 getFPS() { return float32(1000) / m_LastTime_ms; }
    private:
        float32 m_DeltaTime = 0;
        float32 m_LastTime_ms = 0;
        const uint32 m_FPS = 60;
        // Using chrono sleep will be less accurate but
        // it will use less CPU energy.
        bool m_SleepInstead = false;
    };
}
