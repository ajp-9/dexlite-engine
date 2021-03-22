#pragma once

#include "../Util/Time/DeltaTime.hpp"
#include "../Application/Application.hpp"
#include "../Renderer/Renderer.hpp"
#include "Program/Program.hpp"
#include "../Util/EntryPoint.hpp"

int main(int argc, char** argv);

namespace nim
{
	// Core engine.
	class NimbleEngine
	{
		static void Init();
		static void Shutdown();

		template <class T>
		static inline void setProgram()
		{
			m_Program = std::make_shared<T>();
		}
		static void run();
		static void shutdown();
	public:
		static bool m_Running;

		// Is a unique ptr because of inheritance.
		static std::shared_ptr<Program> m_Program;

		static DeltaTime m_DeltaTime;

		static Application m_Application;
		static Renderer m_Renderer;
	public:
		friend int ::main(int argc, char** argv);
	};
}
