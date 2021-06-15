#include "DeltaTime.hpp"

#include <thread>
#include <iostream>

void dex::DeltaTime::start()
{
    m_startTimepoint = std::chrono::high_resolution_clock::now();
}

void dex::DeltaTime::end()
{
    auto endTimepoint = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_startTimepoint).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::nanoseconds>(endTimepoint).time_since_epoch().count();

    auto ns = end - start;
    m_LastTimeDuration_ms = ns * .000001;
}

void dex::DeltaTime::sleep()
{
    if (!m_SleepInstead)
    {
        auto last = getCurrentTime();
        while (getCurrentTime() < last + (1000.0f / m_FPS) - .5) {}
    }
    else
    {
        // "- 1" at the end, sleep_for is 1ms off but change for different hardwares
        std::this_thread::sleep_for(std::chrono::duration<float32, std::milli>(((1000.0f / m_FPS) - m_DeltaTime) - 2));
    }
}

float32 dex::DeltaTime::getDeltaTime()
{
    return m_LastTimeDuration_ms;
}

float32 dex::DeltaTime::getFPS()
{
    return float32(1000) / m_LastTimeDuration_ms;
}

float32 dex::DeltaTime::getCurrentTime()
{
    auto ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock().now()).time_since_epoch().count();
    return ns * .000001;
}
