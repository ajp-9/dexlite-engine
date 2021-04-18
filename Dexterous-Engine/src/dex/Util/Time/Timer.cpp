#include "Timer.hpp"

#include <iostream>

namespace dex
{
	Timer::Timer(const char* name)
		: m_Name(name), m_Stopped(false)
	{
		if (m_Name == "")
			m_Name= "Anonymous";

		m_startTimepoint = std::chrono::high_resolution_clock::now();
	}

	Timer::~Timer()
	{
		if (!m_Stopped)
			stop();
	}

	void Timer::stop()
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
