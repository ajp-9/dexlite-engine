#pragma once

namespace dex
{
    class Framebuffer
    {
        Framebuffer();
        ~Framebuffer();

        void bind();
        void unbind();

        void resize();
    };
    
}
