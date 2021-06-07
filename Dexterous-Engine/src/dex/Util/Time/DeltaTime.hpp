#pragma once

#include <chrono>

#include "../Typedefs.hpp"

namespace dex
{
	class DeltaTime
	{
		DeltaTime(int fps = 60, bool sleepInstead = false)
			: m_FPS(fps), m_SleepInstead(sleepInstead)
		{}

		void start();
		void end();

		void sleep();
	public:
		double getDeltaTime();
		double getFPS();

		operator float() const { return (float)m_LastTimeDuration_ms; }
	private:
		double getCurrentTime();
	private:
		double m_DeltaTime = 0;
		double m_LastTimeDuration_ms = 0;
		const uint32 m_FPS = 60;
		// Using chrono sleep will be less accurate but
		// it will use less CPU energy.
		bool m_SleepInstead = false;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimepoint;

		friend class Engine;
	};
}
