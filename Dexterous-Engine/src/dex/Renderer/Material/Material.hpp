#pragma once

#include <memory>
#include "../Shader/ShaderBase.hpp"
#include "../Material/Texture/Texture.hpp"

namespace dex
{
    namespace Material
    {
        enum class Type : uint8_t
        {
            BASE,
            DEFAULT_3D,
            ALBEDO_3D,
            TEXTURE_3D
        };

        // Shader
        template <class S>
        struct BaseNew
        {
            BaseNew(const std::shared_ptr<S>& shader, Type type = Type::BASE) // link shaders w string of the name
                : m_Shader(shader), m_Type(type)
            {}

            virtual void setUniforms() = 0;
        public:
            std::shared_ptr<S> m_Shader;
            Type m_Type;
        };
        
        // template to link w shader !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~
        struct Base
        {
            Base(const std::shared_ptr<Shader::Base>& shader, Type type = Type::BASE)
                : m_Shader(shader), m_Type(type)
            {}

            virtual void setUniforms() = 0;

            // Put in the template the type of material.
            template <class T>
            inline T& getDerivedSelf()
            {
                if (typeid(T) != typeid(*this))
                    std::cout << "Error: The template input: (" << typeid(T).name() << ") can't be derived from the current object (" << typeid(*this).name() << ").\n";

                return *static_cast<T*>(this);
            }
        public:
            std::shared_ptr<Shader::Base> m_Shader;
            Type m_Type;
        };
    }
}
