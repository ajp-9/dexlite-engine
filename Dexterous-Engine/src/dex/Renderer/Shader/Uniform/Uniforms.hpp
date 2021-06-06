#pragma once

#include <string>

namespace dex
{
	namespace Uniform
	{
		struct Uniform
		{
			Uniform(uint32_t id, const std::string name)
				: m_U_ID(id), m_Name(name)
			{
				//m_ID = glGetUniformLocation()
			}

			uint32_t m_U_ID;
			const std::string m_Name;
		};

		struct Bool : public Uniform
		{
			Bool(uint32_t id, const std::string name)
				: Uniform(id, name)
			{
			}

			void set(bool b)
			{

			}
		};
	}
}
