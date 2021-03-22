#pragma once

#include <memory>

namespace nim
{
	class Program
	{
	public:
		virtual void begin() = 0;
		virtual void end() = 0;

		virtual void update() = 0;
		virtual void render() = 0;
	};
}
