#pragma once

#include "../Core/Program/Program.hpp"
#include "../Core/NimbleEngine.hpp"

#define NIMBLE_DEFINE_MAIN(Game) int main() { nim::NimbleEngine engine({std::shared_ptr<Game>()}); engine.run(); return 0; }
