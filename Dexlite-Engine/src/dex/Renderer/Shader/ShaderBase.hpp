#pragma once

#include <string>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderManager.hpp"

namespace dex
{
    namespace Shader
    {
        // global get lights n persp
        // add prep func thing ^

        class Base
        {
        public:
            Base();
            Base(const std::string& src, const std::string& name = "Base", Type type = Type::BASE);

            ~Base();

            void bind() const;
            void unbind() const;

            //virtual void setProjectionViewMatrix(const glm::mat4& mat) {};
            //virtual void setModelMatrix(const glm::mat4& mat) {};

            void setInt(const std::string& name, int value) const;
            void setFloat(const std::string& name, float32 value) const;

            const std::string& getName() const { return m_Name; }

            const uint32 getID() const { return m_ProgramID; }

            virtual void updateGlobalUniforms();

            // Put in the template the type of material.
            template <class T>
            inline T& getDerivedSelf()
            {
                if (typeid(T) != typeid(*this))
                    std::cout << "Error: The template input: (" << typeid(T).name() << ") can't be derived from the current object (" << typeid(*this).name() << ").\n";

                return *static_cast<T*>(this);
            }
        private:
            void checkShaderErrors(unsigned int shader, std::string type);
        protected:
            uint32 m_ProgramID = 0;
            const std::string m_Name;
            Type m_Type;
        };
    }
}
