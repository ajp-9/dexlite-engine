#pragma once

namespace nim
{
	class Program
	{
	public:
		virtual void Begin() = 0;
		virtual void End() = 0;

		virtual void update() = 0;
		virtual void render() = 0;
	};
}
