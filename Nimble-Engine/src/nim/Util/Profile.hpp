#pragma once

#ifdef PROFILE
#include "Timer.hpp"
#define NIM_PROFILE_SCOPE(name) nim::Timer Timer(name)
#else
#define NIM_PROFILE_SCOPE
#endif