#pragma once

#include "../Core/Program/Program.hpp"
#include "../Core/NimbleEngine.hpp"

#define NIMBLE_DEFINE_MAIN(Game) int main() { nim::NimbleEngine engine(std::make_shared<Game>()); engine.run(); return 0; }
