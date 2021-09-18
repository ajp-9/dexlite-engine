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
            NONE,
            BASE,
            DEFAULT_3D,
            ALBEDO_3D,
            TEXTURE_3D
        };

        struct BaseNew
        {
            BaseNew(std::string name, Type type = Type::NONE) // link shaders w string of the name
                : m_Name(name), m_Type(type)
            {}

            virtual void setUniforms() = 0;
        public:
            std::string m_Name;
            Type m_Type;
        };

        template <class S> // Shader
        struct Interface : BaseNew
        {
            Interface(const std::shared_ptr<S>& shader, std::string name, Type type = Type::NONE)
                : BaseNew(name, type), m_Shader(shader)
            {}
        public:
            std::shared_ptr<S> m_Shader;
        };





        // enter the gross zone -------------------

        // template to link w shader !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~
        /*struct Base
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
        };*/
    }
}
