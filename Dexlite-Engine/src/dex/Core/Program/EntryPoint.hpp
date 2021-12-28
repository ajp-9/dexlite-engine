#pragma once

int main(int argc, char** argv);

#define DEXLITE_DEFINE_MAIN(Program)                \
int main(int argc, char** argv)                     \
{                                                   \
    dex::Engine::Init(std::make_shared<Program>()); \
    dex::Engine::Run();                             \
    return 0;                                       \
}                                                   \
