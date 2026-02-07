#pragma once

#include <cmath>
#include "Math\MathInternal.hpp"

namespace Mathematics
{
    struct vec3;
    struct mat4;

    struct quat
    {
    private:
        float m_W;
        float m_X, m_Y, m_Z;

    public:
        quat(float qw, const vec3& xyz);
        quat(float qw, float qx, float qy, float qz) : m_W(qw), m_X(qx), m_Y(qy), m_Z(qz) {}

        static quat identity() { return quat(1.0f, 0.0f, 0.0f, 0.0f); }

        float w() const { return m_W; } 
        float x() const { return m_X; } 
        float y() const { return m_Y; } 
        float z() const { return m_Z; } 
        
        vec3 xyz() const;
        vec3 zyx() const;

        quat& normalized()
        {
            float l = this->length();

            float invLen = 1.0f / l;

            m_W *= invLen;
            m_X *= invLen;
            m_Y *= invLen;
            m_Z *= invLen;

            return *this;
        }
        quat getUnitQuat() const
        {
            quat copy = *this;

            return copy.normalized();
        }

        quat& conjugated()
        {
            m_X *= -1.0f;
            m_Y *= -1.0f;
            m_Z *= -1.0f;

            return *this;
        }
        quat getConjugatedQuat() const
        {
            quat copy = *this;

            return copy.conjugated();
        }

        float length() const 
        {
            return std::sqrtf( (m_W * m_W) + (m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z) );
        }

        static float length(const quat& quat)
        {
            return std::sqrtf( (quat.m_W * quat.m_W) + (quat.m_X * quat.m_X) + (quat.m_Y * quat.m_Y) + (quat.m_Z * quat.m_Z) );
        }

        static quat fromAxisAngle(vec3 axis, float angle);

        static quat fromEuler(const vec3& rotation);

        mat4 toMat4() const;

        static vec3 rotatePointViaQuat(const vec3& point, const quat& rot);

        vec3 toEuler() const;
    };

    inline quat operator*(const quat& a, const quat& b);
}