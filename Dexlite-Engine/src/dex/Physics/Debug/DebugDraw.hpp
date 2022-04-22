#pragma once

namespace dex
{
    class DebugDraw : public btIDebugDraw
    {
        virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
        {

        }

        virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {}

        virtual void reportErrorWarning(const char* warningString) {};
        virtual void draw3dText(const btVector3& location, const char* textString) {};
        virtual void setDebugMode(int debugMode) { d = debugMode; }
        virtual int getDebugMode() const { return d; };

        int d = 1;
    };
}
