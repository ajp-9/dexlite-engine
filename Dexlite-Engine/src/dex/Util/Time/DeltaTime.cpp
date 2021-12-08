#include "DeltaTime.hpp"

#include <thread>
#include <iostream>
#include <GLFW/glfw3.h>

void dex::DeltaTime::doCycle()
{
    float32 current_time = glfwGetTime();
    m_DeltaTime = (m_LastTime_ms > 0.0f) ? current_time - m_LastTime_ms : 0;
    std::cout << m_DeltaTime << "\n";
    m_LastTime_ms = current_time;
}

void dex::DeltaTime::sleep()
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

float32 dex::DeltaTime::getDeltaTime()
{
    return m_DeltaTime;
}

float32 dex::DeltaTime::getFPS()
{
    return float32(1000) / m_LastTime_ms;
}

float32 dex::DeltaTime::getCurrentTime()
{
    auto ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock().now()).time_since_epoch().count();
    return ns * .000001;
}
