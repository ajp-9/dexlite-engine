#pragma once

#include <string>

namespace dex
{
	namespace Component
	{
		struct Tag
		{
			Tag(const char* tag)
				: m_Tag(tag)
			{}
			Tag(const std::string& tag)
				: m_Tag(tag)
			{}
			
			std::string m_Tag;
		};
	}
}
