#pragma once

namespace zim
{
	class Program
	{
	public:
		virtual void Init() = 0;
		virtual void Shutdown() = 0;

		virtual void update() = 0;
		virtual void render() = 0;
	};
}
