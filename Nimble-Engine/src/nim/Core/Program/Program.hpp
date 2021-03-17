#pragma once

class NimbleEngine;

namespace nim
{
	class Program
	{
	public:
		Program(NimbleEngine& engine);
		~Program();

		virtual void onBegin() = 0;
		virtual void onEnd() = 0;

		virtual void onUpdate() = 0;
		virtual void onRender() = 0;

		NimbleEngine& m_Engine;
	};
}
