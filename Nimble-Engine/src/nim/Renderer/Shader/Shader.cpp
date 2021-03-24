#include "Shader.hpp"

#include <glad/glad.h>
#include <iostream>
#include <fstream>

namespace nim
{
	Shader::Shader(const std::string& src)
	{
		std::ifstream source;
		source.open(src);

		std::string vertex;
		std::string fragment;

		if (0)
		{
			std::string line;

			bool isVertex = false;
			bool isFragment = false;

			while (std::getline(source, line))
			{
				if (!line.find("#type VERTEX"))
				{
					isVertex = true;
					isFragment = false;

					continue;
				}

				if (!line.find("#type FRAGMENT"))
				{
					isFragment = true;
					isVertex = false;

					continue;
				}

				if (isVertex)
					vertex.append(line + "\n");
				else if (isFragment)
					fragment.append(line + "\n");
			}
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
	}

	void Shader::unbind() const
	{
	}
}
