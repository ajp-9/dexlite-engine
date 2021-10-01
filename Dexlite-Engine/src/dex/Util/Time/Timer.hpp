#pragma once

#include <chrono>

namespace dex
{
    // Times the amount of time it takes in a scope.
    // Prints the time in ms, with ns resolution.
    class Timer
    {
    public:
        Timer(const char* name = "Anonymous");
        ~Timer();

        void stop();
    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimepoint;
        bool m_Stopped;
    };
}
