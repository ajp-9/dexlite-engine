#pragma once

int main(int argc, char** argv);

#define DEXLITE_DEFINE_MAIN(Program)\
                                    \
int main(int argc, char** argv)     \
{                                   \
    dex::Engine<Program> Engine;    \
                                    \
    Engine.Run();                   \
                                    \
    return 0;                       \
}                                   
