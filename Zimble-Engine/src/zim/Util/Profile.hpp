#pragma once

#ifdef ZIM_ENABLE_PROFILE
#include "Time/Timer.hpp"
#define ZIM_PROFILE_SCOPE(name) zim::Timer Timer(name)
#else
#define ZIM_PROFILE_SCOPE
#endif
