#pragma once

#include <vector>

#include "../../DataTypes/DataTypes.hpp"

namespace dex
{
	namespace Shader
	{
		class Base;

		class UniformBufferObject
		{
		public:
			// Need to .bindShader() in order to get block size & the specifications.
			UniformBufferObject();

			// UBO in shader should NOT change because it is being set everytime you bind another shader.
			void bindShader(const std::shared_ptr<Shader::Base>& shader, const char* ubo_name);
			// Do this AFTER you've bound all the shaders.
			void setup();

			/*
			Important:
			 - Everything should be inside a struct, (or an array of structs)
			 with the struct having "__declspec(align(16))" infront of the it.
			 - All glm types should also have "__declspec(align(16))" in front of them.
			 - No bools! Use uint's or int's instead.
			*/
			void uploadData(const void* data);

			void bind();
			void unbind();
		private:
			uint32_t m_ID = 0;
			int32_t m_BlockSize = 0;

			// Universal binding index for the UBO
			uint32_t m_BlockBinding = 0;

			static uint32_t s_NextBlockBinding;
		};
	}
}