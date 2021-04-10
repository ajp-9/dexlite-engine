#pragma once

#include <string>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace zim
{
	class Shader
	{
	public:
		Shader(const char* src);
		~Shader();

		void setLocations();

		void setProjectionViewMatrix(const glm::mat4& mat);
		void setModelMatrix(const glm::mat4& mat);

		void bind() const;
		void unbind() const;

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
	private:
		void checkShaderErrors(unsigned int shader, std::string type);
	private:
		uint32_t m_ProgramID = 0;
		uint8_t m_Type = 0;

		uint32_t u_ProjectionViewMatrix_Location = 0;
		uint32_t u_ModelMatrix_Location = 0;
	};
}
