#include "Shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <fstream>

namespace zim
{
	Shader::Shader(const char* src, const char* name)
		: m_Name(name)
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

	Shader::~Shader()
	{
		glDeleteProgram(m_ProgramID);
	}

	void Shader::bind() const
	{
		glUseProgram(m_ProgramID);
	}

	void Shader::unbind() const
	{
		glUseProgram(0);
	}

	void Shader::setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), (int)value);
	}

	void Shader::setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value);
	}

	void Shader::setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_ProgramID, name.c_str()), value);
	}

	void Shader::setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &value[0]);
	}
	void Shader::setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(m_ProgramID, name.c_str()), x, y);
	}

	void Shader::setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &value[0]);
	}
	void Shader::setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(m_ProgramID, name.c_str()), x, y, z);
	}

	void Shader::setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &value[0]);
	}
	void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(m_ProgramID, name.c_str()), x, y, z, w);
	}

	void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
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
