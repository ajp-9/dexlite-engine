#pragma once

#include <vector>

#include "../../../DataTypes/DataTypes.hpp"
#include "../../Shader/ShaderBase.hpp"

namespace dex
{
	class UniformBufferObject
	{
	public:
		// Need to .bindShader() in order to get block size & the specifications
		UniformBufferObject();
		
		// UBO in shader should NOT change because it is being set everytime you bind another shader
		void bindShader(const std::shared_ptr<Shader::Base>& shader, const char* ubo_name);

		template <typename T>
		void uploadData(const T data);

		void bind();
		void unbind();
	public:
		uint32_t m_ID = 0;
		int32_t m_BlockSize = 0;

		uint32_t m_InternalBlockBinding = 0;
		uint32_t m_BlockBinding = 0;
		static uint32_t s_NextBlockBinding;
	};

	template<typename T>
	inline void UniformBufferObject::uploadData(const T data)
	{
	}
}
