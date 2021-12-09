#include "Time.hpp"

#include <thread>
#include <iostream>
#include <GLFW/glfw3.h>

void dex::Time::doCycle()
{
    float32 current_time = glfwGetTime();
    m_DeltaTime = (m_LastTime_ms > 0.0f) ? current_time - m_LastTime_ms : 0;
    m_LastTime_ms = current_time;
}

void dex::Time::sleep()
{
    if (!m_SleepInstead)
    {
        float32 last = m_DeltaTime;
        while (glfwGetTime() < m_LastTime_ms + (1.0f / m_FPS)) {}
    }
    else
    {
        // "- 1" at the end, sleep_for is 1ms off but change for different hardwares
        std::this_thread::sleep_for(std::chrono::duration<float32, std::milli>(((1000.0f / m_FPS) - m_DeltaTime) - 2));
    }
}
