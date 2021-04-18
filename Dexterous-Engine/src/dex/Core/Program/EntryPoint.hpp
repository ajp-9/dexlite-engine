#pragma once

int main(int argc, char** argv);
#define ZIMBLE_DEFINE_MAIN(Program) int main(int argc, char** argv) {dex::Engine::Init(std::make_shared<Program>());dex::Engine::run();return 0;}

/*
//Macro expands to this:
int main(int argc, char** argv)
{
	//dex::Engine::Init(std::make_shared<Program>());
	//dex::Engine::run();
	return 0;
}
*/
