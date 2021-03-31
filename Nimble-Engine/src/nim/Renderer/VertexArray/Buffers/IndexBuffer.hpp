#pragma once

#include <cstdint>
#include <vector>

namespace nim
{
	class IndexBuffer
	{
	public:
		IndexBuffer();

		void uploadData(std::vector<unsigned int>& indices);

		void bind();
		void unbind();

		uint32_t getCount() const { return m_Count; }
	private:
		uint32_t m_ID = 0;
		uint32_t m_Count = 0;
	};
}
