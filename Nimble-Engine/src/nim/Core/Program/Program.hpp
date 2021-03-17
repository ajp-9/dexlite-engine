#pragma once

namespace nim
{
	class Program
	{
	public:
		Program();
		~Program();

		virtual void onBegin() = 0;
		virtual void onEnd() = 0;

		virtual void onUpdate() = 0;
		virtual void onRender() = 0;
	};
}
