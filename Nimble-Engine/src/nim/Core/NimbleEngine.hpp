#pragma once

#include "../Util/Time/DeltaTime.hpp"
#include "../Application/Application.hpp"
#include "../Renderer/Renderer.hpp"
#include "Program/Program.hpp"

namespace nim
{
	class Program;

	// Core engine.
	class NimbleEngine
	{
	public:
		NimbleEngine();
		~NimbleEngine();

		template <class T>
		inline void setProgram()
		{
			m_Program = std::make_shared<T>();
			m_Program->setEngineHandle(m_EngineHandle);
		}

		void run();
		void shutdown();
	public:
		bool m_Running = false;

		// Is a unique ptr because of inheritance.
		std::shared_ptr<Program> m_Program;
		std::shared_ptr<EngineHandle> m_EngineHandle;

		DeltaTime m_DeltaTime;

		Application m_Application;
		Renderer m_Renderer;
	};
}
