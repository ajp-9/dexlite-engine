#pragma once

#include <vector>

#include "../../../../Util/Typedefs.hpp"

namespace dex
{
	class IndexBuffer
	{
	public:
		IndexBuffer();

		void uploadData(const std::vector<uint32_t>& indices);

		void bind();
		void unbind();

		uint32 getCount() const { return m_Count; }
	private:
		uint32 m_ID = 0;
		uint32 m_Count = 0;
	};
}
