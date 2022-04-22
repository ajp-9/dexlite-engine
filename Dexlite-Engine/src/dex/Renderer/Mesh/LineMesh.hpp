#pragma once

#include <glad/gl.h>
#include <vector>
#include "Vertex/LineVertex3D.hpp"
#include "VertexArray/Buffers/VertexBuffer.hpp"

namespace dex
{
    class LineMesh3D
    {
    public:
        void drawNew()
        {
            if (m_VBO_ID)
                glDeleteBuffers(1, &m_VBO_ID);

            if (m_ID)
                glDeleteVertexArrays(1, &m_ID);

            if (Vertices.size())
            {
                glGenVertexArrays(1, &m_ID);
                bind();

                glGenBuffers(1, &m_VBO_ID);
                //glLineWidth(2);
                
                glBindBuffer(GL_ARRAY_BUFFER, m_VBO_ID);
                glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(LineVertex3D), &Vertices[0], GL_STATIC_DRAW);
                
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex3D), nullptr);
                glEnableVertexAttribArray(0);

                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex3D), (void*)(3 * sizeof(float)));
                glEnableVertexAttribArray(1);

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(0);

                bind();

                glDrawArrays(GL_LINES, 0, Vertices.size());
                Vertices.clear();
            }
        }

        void bind()
        {
            glBindVertexArray(m_ID);
        }

        void addLine(const glm::vec3& from, const glm::vec3& to, const glm::vec3& color)
        {
            Vertices.push_back({ from, color });
            Vertices.push_back({ to, color });
        }

        std::vector<LineVertex3D> Vertices;
    private:
        GLuint m_ID = 0;
        GLuint m_VBO_ID = 0;
    };
}
