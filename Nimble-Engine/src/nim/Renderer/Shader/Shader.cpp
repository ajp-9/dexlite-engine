#include "Shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <fstream>

namespace nim
{
	Shader::Shader(const char* src)
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
			m_ID = glCreateProgram();
			glAttachShader(m_ID, vertex);
			glAttachShader(m_ID, fragment);
			glLinkProgram(m_ID);
			checkShaderErrors(m_ID, "PROGRAM");

			glDeleteShader(vertex);
			glDeleteShader(fragment);
		}
		else
		{
			std::cout << "Shader at source: " << src << ", is invalid!\n";
		}
	}

	Shader::~Shader()
	{
	}

	void Shader::bind() const
	{
		glUseProgram(m_ID);
	}

	void Shader::unbind() const
	{
		glUseProgram(0);
	}

	void Shader::setMat4Uniform(const char* name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::checkShaderErrors(unsigned int shader, std::string type)
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
