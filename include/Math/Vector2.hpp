#pragma once

#include "Math\MathInternal.hpp"

namespace Mathematics
{
    struct Vec2
    {
    private:
        float m_X, m_Y;

    public:
        Vec2(float vx, float vy) : m_X(vx), m_Y(vy) {}
        Vec2(const Angle& angle) : m_X(MathInternal::Cos(angle.AsRadians())), m_Y(MathInternal::Sin(angle.AsRadians())) {}

        float X() { return m_X; }
        float Y() { return m_Y; }
        Vec2 XY() { return Vec2(m_X, m_Y); }

        float Length()
        {
            return MathInternal::Sqrt(MathInternal::Pow(m_X, 2.0f) + MathInternal::Pow(m_Y, 2.0f));
        }
        float LengthSquared()
        {
            return MathInternal::Pow(m_X, 2.0f) + MathInternal::Pow(m_Y, 2.0f);
        }

        Vec2& Normalized()
        {
            float l = this->LengthSquared();
            if (l == 0.0f) return *this;

            m_X /= l; 
            m_Y /= l;

            return *this;
        }

        float DotProduct(const Vec2& other)
        {
            return m_X * other.m_X + m_Y * other.m_Y; 
        }

        float Distance(const Vec2& other)
        {
            return MathInternal::Sqrt(MathInternal::Pow(other.m_X - m_X, 2.0f) + MathInternal::Pow(other.m_Y - m_Y, 2.0f));
        }
        float DistanceSquared(const Vec2& other)
        {
            return MathInternal::Pow(other.m_X - m_X, 2.0f) + MathInternal::Pow(other.m_Y - m_Y, 2.0f);
        }

        // TODO: need to implement static methods
    };


    
}