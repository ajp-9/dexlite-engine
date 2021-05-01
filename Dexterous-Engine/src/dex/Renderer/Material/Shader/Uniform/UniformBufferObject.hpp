#pragma once

#include <vector>

#include "../../../DataTypes/DataTypes.hpp"

namespace dex
{
	class UniformBufferObject
	{
	public:
		UniformBufferObject();

		void setLayout(const std::vector<Data::Type>& types);

		template <typename T>
		void uploadData(T data);

		void bind();
		void unbind();
	private:
		uint32_t m_ID;
	};

	template<typename T>
	inline void UniformBufferObject::uploadData(T data)
	{
	}
}
