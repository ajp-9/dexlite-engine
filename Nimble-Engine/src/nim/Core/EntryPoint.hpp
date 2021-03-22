#pragma once

#include "../Core/Program/Program.hpp"
#include "../Core/NimbleEngine.hpp"
#include <iostream>

#define NIMBLE_DEFINE_MAIN(Program) int main(int argc, char** argv) {nim::NimbleEngine::Init(std::make_shared<Program>());nim::NimbleEngine::run();return 0;}

/*
//Macro expands to this:
int main(int argc, char** argv)
{
	//nim::NimbleEngine::Init(std::make_shared<Program>());
	//nim::NimbleEngine::run();
	return 0;
}
*/