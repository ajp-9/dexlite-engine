#include "ShaderBase.hpp"

#include <glad/glad.h>
#include <iostream>
#include <fstream>

namespace dex
{
    namespace Shader
    {
        Base::Base()
            : m_Name("Base"), m_Type(Type::BASE)
        {}

        Base::Base(const char* src, const char* name, Type type)
            : m_Name(name), m_Type(type)
        {
            std::ifstream source;
            source.open(std::string(src));
            
            std::string srcVertex, srcFragment;

            if (source.is_open())
            {
                std::string line;

                bool isVertex = false;
                bool isFragment = false;

                while (std::getline(source, line))
                {
                    if (line.find("#type VERTEX") != std::string::npos)
                    {
                        isVertex = true;
                        isFragment = false;

                        continue;
                    }

                    if (line.find("#type FRAGMENT") != std::string::npos)
                    {
                        isFragment = true;
                        isVertex = false;

                        continue;
                    }

                    if (isVertex)
                        srcVertex.append(line + "\n");
                    else if (isFragment)
                        srcFragment.append(line + "\n");
                }

                const char* cSrcVertex = srcVertex.c_str();
                const char* cSrcFragment = srcFragment.c_str();

                // Vertex shader.
                unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertex, 1, &cSrcVertex, NULL);
                glCompileShader(vertex);
                checkShaderErrors(vertex, "VERTEX");

                // Fragment shader
                unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragment, 1, &cSrcFragment, NULL);
                glCompileShader(fragment);
                checkShaderErrors(fragment, "FRAGMENT");

                // Shader program
                m_ProgramID = glCreateProgram();
                glAttachShader(m_ProgramID, vertex);
                glAttachShader(m_ProgramID, fragment);
                glLinkProgram(m_ProgramID);
                checkShaderErrors(m_ProgramID, "PROGRAM");

                glDeleteShader(vertex);
                glDeleteShader(fragment);
            }
            else
            {
                std::cout << "Shader at source: " << src << ", is invalid!\n";
            }
        }

        Base::~Base()
        {
            //std::cout << "delet " << "\n";
            glDeleteProgram(m_ProgramID);
        }

        void Base::bind() const
        {
            glUseProgram(m_ProgramID);
        }

        void Base::unbind() const
        {
            glUseProgram(0);
        }

        void Base::setInt(const std::string& name, int value) const
        {
            glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value);
        }

        void Base::setFloat(const std::string& name, float32 value) const
        {
            glUniform1f(glGetUniformLocation(m_ProgramID, name.c_str()), value);
        }

        void Base::checkShaderErrors(unsigned int shader, std::string type)
        {
            GLint success;
            GLchar infoLog[1024];
            if (type != "PROGRAM")
            {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n";
                }
            }
            else
            {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n";
                }
            }
        }
    }
}
