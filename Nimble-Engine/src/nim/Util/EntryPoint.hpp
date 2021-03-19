#pragma once

#include "../Core/Program/Program.hpp"
#include "../Core/NimbleEngine.hpp"

#define NIMBLE_DEFINE_MAIN(Program) int main() { nim::NimbleEngine engine; engine.setProgram<Program>(); engine.run(); return 0; }

/* Macro expands to this:
int main()
{
	nim::NimbleEngine engine;
	engine.setProgram<Program>();
	engine.run();
	return 0;
}
*/
