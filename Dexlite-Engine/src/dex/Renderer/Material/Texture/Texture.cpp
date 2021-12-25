#include "Texture.hpp"

#include <glad/glad.h>
#include <stb_image.h>

#include <iostream>

#include "../../../Util/Logging.hpp"

namespace dex
{
    Texture::Texture(const char* src, bool blending)
    {
        glGenTextures(1, &m_ID);
        bind(); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters

        if (!blending)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }

        // load image, create texture, and generate mipmaps
        //stbi_set_flip_vertically_on_load(true);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(src, &width, &height, &nrChannels, 0); // maybe change to 0 from 43
        if (data)
        {
            if (nrChannels == 4) // checks if png or not
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
            else // if else then load as .jpg (RGB) only
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.5);
        }
        else
        {
            DEX_LOG_ERROR("<Texture::Texture>: File at {} failed to load!\n", src);
        }

        stbi_image_free(data);
        unbind();
    }

    Texture::Texture(std::vector<uint8> image, const tinygltf::Sampler& sampler, glm::ivec2 dimensions, GLenum format, bool blending)
    {
        glGenTextures(1, &m_ID);
        bind();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sampler.wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, sampler.wrapT);
        // set texture filtering parameters
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (sampler.minFilter != -1) ? sampler.minFilter : GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (sampler.magFilter != -1) ? sampler.magFilter : GL_LINEAR);

        // Manually vertically flip image because tinygltf doesn't do it for us.
        //stbi__vertical_flip(&image.at(0), dimensions.x, dimensions.y, sizeof(unsigned int));

        glTexImage2D(GL_TEXTURE_2D, 0, format, dimensions.x, dimensions.y, 0, format, GL_UNSIGNED_BYTE, &image.at(0));
        
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.5);

        unbind();
    }
}
