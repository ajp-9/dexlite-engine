#pragma once

#include <memory>
#include "../../Shader/Shader.hpp"
#include "../../Texture/Texture.hpp"

namespace dex
{
	namespace Material
	{
		enum class Type : uint8_t
		{
			DEFAULT,
			ALBEDO_3D,
			TEXTURE_3D
		};

		struct Material
		{
			Material(const std::weak_ptr<Shader::Shader>& shader, Type type = Type::DEFAULT)
				: m_Shader(shader), m_Type(type)
			{}

			virtual void setUniforms() {};

			// Put in the template the type of material.
			template <class T>
			inline T& getSelf()
			{
				return *static_cast<T*>(this);
			}

			std::weak_ptr<Shader::Shader> m_Shader;
		private:
			Type m_Type;
		};
	}
}
