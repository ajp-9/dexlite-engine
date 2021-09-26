#pragma once

#include <spdlog/spdlog.h>

#define DEX_LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define DEX_LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define DEX_LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define DEX_LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)
