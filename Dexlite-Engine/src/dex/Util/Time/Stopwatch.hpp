#pragma once

#include <chrono>
#include <string>

namespace dex
{
    // Times the amount of time it takes in a scope.
    // Prints the time in ms, with ns resolution.
    class Stopwatch
    {
    public:
        Stopwatch(const std::string& name = "Anonymous");
        ~Stopwatch();

        void stop();
    private:
        std::string m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimepoint;
        bool m_Stopped;
    };
}
