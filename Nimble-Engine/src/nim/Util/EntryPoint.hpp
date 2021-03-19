#pragma once

#include "../Core/Program/Program.hpp"
#include "../Core/NimbleEngine.hpp"

#define NIMBLE_DEFINE_MAIN(Game)                                           \
int main()                                                                 \
{                                                                          \
	nim::NimbleEngine engine;                                              \
	std::shared_ptr<nim::Program> program = std::make_shared<SandBox>();   \
	program->setEngineHandle(std::make_shared<nim::EngineHandle>(engine)); \
	engine.setProgram(program);	                                           \
	engine.run();                                                          \
	return 0;                                                              \
}