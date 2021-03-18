#pragma once

#include <memory>

#include "../Handle/EngineHandle.hpp"

namespace nim
{
	class Program
	{
	public:
		virtual void begin() = 0;
		virtual void end() = 0;

		virtual void update() = 0;
		virtual void render() = 0;

		std::shared_ptr<EngineHandle> m_EngineHandle;
	};
}
