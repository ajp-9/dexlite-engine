#pragma once

namespace dex
{
    class Program
    {
    public:
        virtual void beginFrame() = 0;

        virtual void update() = 0;
        virtual void render() = 0;

        virtual void endFrame() = 0;
    public:
        bool Running = true;
    };
}
