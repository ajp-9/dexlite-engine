#pragma once

#include "../Core/Program/Program.hpp"
#include "../Core/ZimbleEngine.hpp"
#include <iostream>

int main(int argc, char** argv);
#define NIMBLE_DEFINE_MAIN(Program) int main(int argc, char** argv) {zim::ZimbleEngine::Init(std::make_shared<Program>());zim::ZimbleEngine::run();return 0;}

/*
//Macro expands to this:
int main(int argc, char** argv)
{
	//zim::ZimbleEngine::Init(std::make_shared<Program>());
	//zim::ZimbleEngine::run();
	return 0;
}
*/