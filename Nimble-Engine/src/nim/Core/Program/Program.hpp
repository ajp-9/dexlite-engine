#pragma once

class NimbleEngine;

namespace nim
{
	class Program
	{
	public:
		virtual void begin() = 0;
		virtual void end() = 0;

		virtual void update() = 0;
		virtual void render() = 0;

		//NimbleEngine& m_Engine;
	};
}
