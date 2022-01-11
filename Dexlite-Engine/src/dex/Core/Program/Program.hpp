#pragma once

#include "../EngineConfig.hpp"

namespace dex
{
    class Program
    {
    public:
        virtual void SetEngineConfig() = 0;

        virtual void Init() = 0;
        virtual void Shutdown() = 0;

        virtual void update() = 0;
        virtual void render() = 0;
        
        EngineConfig EngineConfig;
    };
}
