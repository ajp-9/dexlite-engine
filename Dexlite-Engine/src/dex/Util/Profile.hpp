#pragma once

#ifdef DEX_ENABLE_PROFILE
#include "Time/Stopwatch.hpp"
#define DEX_PROFILE_SCOPE(name) dex::Timer Timer(name)
#else
#define DEX_PROFILE_SCOPE
#endif
