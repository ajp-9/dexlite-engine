#include "Stopwatch.hpp"

#include <iostream>

namespace dex
{
    Stopwatch::Stopwatch(const std::string& name)
        : m_Name(name), m_Stopped(false)
    {
        m_startTimepoint = std::chrono::high_resolution_clock::now();
    }

    Stopwatch::~Stopwatch()
    {
        if (!m_Stopped)
            stop();
    }

    void Stopwatch::stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_startTimepoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::nanoseconds>(endTimepoint).time_since_epoch().count();

        auto ns = end - start;
        auto us = ns * .001;
        auto ms = ns * .000001;

        std::cout << m_Name << ": " << ms << " ms\n";

        m_Stopped = true;
    }
}
