#pragma once

#include <vector>

#include "Vertex.hpp"
#include "../VertexArray/VertexArray.hpp"
#include "Material.hpp"

namespace nim
{
	template <typename V>
	class Mesh
	{
	public:
		Mesh(const Material& material)
			: m_Material(material)
		{
		}

		void render()
		{
			m_VertexArray.render();
		}

		std::weak_ptr<Shader>& getShader()
		{
			return m_Material.m_Shader;
		}
	private:
		std::vector<V> m_Vertices;
		GL::VertexArray<V> m_VertexArray;

		Material m_Material;
	};
}
