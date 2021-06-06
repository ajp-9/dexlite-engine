#pragma once

#include <string>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderManager.hpp"

namespace dex
{
	namespace Shader
	{
		class Base
		{
		public:
			Base();
			Base(const char* src, const char* name = "Base", Type type = Type::BASE);

			~Base();

			void bind() const;
			void unbind() const;

			virtual void setProjectionViewMatrix(const glm::mat4& mat) {};
			virtual void setModelMatrix(const glm::mat4& mat) {};

			void setBool(const std::string& name, bool value) const;
			void setInt(const std::string& name, int value) const;
			void setFloat(const std::string& name, float value) const;
			void setVec2(const std::string& name, const glm::vec2& value) const;
			void setVec2(const std::string& name, float x, float y) const;
			void setVec3(const std::string& name, const glm::vec3& value) const;
			void setVec3(const std::string& name, float x, float y, float z) const;
			void setVec4(const std::string& name, const glm::vec4& value) const;
			void setVec4(const std::string& name, float x, float y, float z, float w);
			void setMat2(const std::string& name, const glm::mat2& mat) const;
			void setMat3(const std::string& name, const glm::mat3& mat) const;
			void setMat4(const std::string& name, const glm::mat4& mat) const;

			const std::string& getName() const { return m_Name; }

			const uint32_t getID() const { return m_ProgramID; }

			// Put in the template the type of material.
			template <class T>
			inline T& getDerivedSelf()
			{
				if (typeid(T) != typeid(*this))
					std::cout << "Error: The template input: (" << typeid(T).name() << ") can't be derived from the current object (" << typeid(*this).name() << ").\n";

				return *static_cast<T*>(this);
			}
		private:
			void checkShaderErrors(unsigned int shader, std::string type);
		protected:
			uint32_t m_ProgramID = 0;
			const std::string m_Name;
			Type m_Type;
		};
	}
}
