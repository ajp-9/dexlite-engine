#pragma once

#include "../../Renderer/Renderer.hpp"

namespace dex
{
    class DebugDraw : public btIDebugDraw
    {
    public:
        DebugDraw(Renderer* renderer)
            : m_Renderer(renderer)
        {}

        virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
        {
            m_Renderer->LineMesh.addLine(glm::vec3(from.x(), from.y(), from.z()), glm::vec3(to.x(), to.y(), to.z()), glm::vec3(color.x(), color.y(), color.z()));
        }

        virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) 
        {
            //m_Renderer->LineMesh.addLine(glm::vec3(PointOnB.x(), PointOnB.y(), PointOnB.z()), glm::vec3(PointOnB.x(), PointOnB.y(), PointOnB.z()) + glm::vec3(normalOnB.x(), normalOnB.y(), normalOnB.z()) * distance, glm::vec3(color.x(), color.y(), color.z()));
            //m_Renderer->LineMesh.addLine(glm::vec3(PointOnB.x(), PointOnB.y(), PointOnB.z()), glm::vec3(PointOnB.x(), PointOnB.y(), PointOnB.z()) + glm::vec3(normalOnB.x(), normalOnB.y(), normalOnB.z()) * glm::vec3(0.01), glm::vec3(0));
        }

        virtual void reportErrorWarning(const char* warningString) {};
        virtual void draw3dText(const btVector3& location, const char* textString) {};
        virtual void setDebugMode(int debugMode) { Mode = debugMode; }
        virtual int getDebugMode() const { return Mode; };
    private:
        Renderer* m_Renderer;

        int Mode = 0;
    };
}
