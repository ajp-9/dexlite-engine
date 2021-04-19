#pragma once

#include <cstdint>
#include <vector>

namespace dex
{
	class IndexBuffer
	{
	public:
		IndexBuffer();

		void uploadData(const std::vector<uint32_t>& indices);

		void bind();
		void unbind();

		uint32_t getCount() const { return m_Count; }
	private:
		uint32_t m_ID = 0;
		uint32_t m_Count = 0;
	};
}
