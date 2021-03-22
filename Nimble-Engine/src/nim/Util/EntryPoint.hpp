#pragma once

#include "../Core/Program/Program.hpp"
#include "../Core/NimbleEngine.hpp"

#define NIMBLE_DEFINE_MAIN(Program) int main(int argc, char** argv) {nim::NimbleEngine::Init();nim::NimbleEngine::setProgram<Program>();nim::NimbleEngine::run();return 0;}

/*
//Macro expands to this:
int main(int argc, char** argv)
{
	nim::NimbleEngine::Init();
	nim::NimbleEngine::setProgram<Program>();
	nim::NimbleEngine::run();
	return 0;
}
*/
