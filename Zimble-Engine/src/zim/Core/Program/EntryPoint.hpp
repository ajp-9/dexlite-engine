#pragma once

int main(int argc, char** argv);
#define ZIMBLE_DEFINE_MAIN(Program) int main(int argc, char** argv) {zim::ZimbleEngine::Init(std::make_shared<Program>());zim::ZimbleEngine::run();return 0;}

/*
//Macro expands to this:
int main(int argc, char** argv)
{
	//zim::ZimbleEngine::Init(std::make_shared<Program>());
	//zim::ZimbleEngine::run();
	return 0;
}
*/