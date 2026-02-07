#pragma once 

#include <cmath>
#include "Math\MathInternal.hpp"

namespace Mathematics
{
    struct vec2;

    struct vec3
    {
    private:
        float m_X, m_Y, m_Z;

    public:
        // Constructor that returns a vec3 with x being 0.0, y being 0.0, z being 0.0
        vec3() : m_X(0.0f), m_Y(0.0f), m_Z(0.0f) {}
        // Constructor that returns a vec3 with x being vx, y being vy and z being vz 
        vec3(float vx, float vy) : m_X(vx), m_Y(vy), m_Z(0.0f) {}
        // Constructor that returns a vec3 with x being vx, y being vy and z being 0.0 
        vec3(float vx, float vy, float vz) : m_X(vx), m_Y(vy), m_Z(vz) {}
        // Constructor that returns a vec3 with x being vec.x, y being vec.y and z being vec.z
        vec3(const vec3& vec) : m_X(vec.m_X), m_Y(vec.m_Y), m_Z(vec.m_Z) {}

        // Constructor that returns a vec3 with x being vec.x, y being vec.y and z being 0.0
        vec3(const vec2& xy);
        // Constructor that returns a vec3 with x being vec.x, y being vec.y and z being vz
        vec3(const vec2& xy, float vz);

        operator vec2() const;

        static vec3 zero() { return vec3(0.0f, 0.0f, 0.0f); }
        static vec3 one() { return vec3(1.0f, 1.0f, 1.0f); }
        static vec3 right() { return vec3(1.0f, 0.0f, 0.0f); }
        static vec3 left() { return vec3(-1.0f, 0.0f, 0.0f); }
        static vec3 up() { return vec3(0.0f, 1.0f, 0.0f); }
        static vec3 down() { return vec3(0.0f, 1.0f, 0.0f); }
        static vec3 forward() { return vec3(0.0f, 0.0f, 1.0f); }
        static vec3 backward() { return vec3(0.0f, 0.0f, -1.0f); }


        float x() const { return m_X; }
        float y() const { return m_Y; }
        float z() const { return m_Z; }

        vec2 xx() const; 
        vec2 yy() const; 
        vec2 zz() const; 
        vec2 xy() const; 
        vec2 xz() const; 
        vec2 yx() const; 
        vec2 yz() const; 
        vec2 zx() const; 
        vec2 zy() const; 

        vec3 xxx() const { return vec3(m_X, m_X, m_X); }
        vec3 yyy() const { return vec3(m_Y, m_Y, m_Y); }
        vec3 zzz() const { return vec3(m_Z, m_Z, m_Z); }

        vec3 xyz() const { return vec3(m_X, m_Y, m_Z); }
        vec3 zyx() const { return vec3(m_Z, m_Y, m_X); }

        // Returns a float pointer of the vector's value at the specified index (x -> 0, y -> 1, z -> 2)
        // The specified index is clamped between 0 and 2
        float* operator[](int index) const
        {
            index = MathInternal::clamp(index, 0.0f, 2.0f);

            if (index == 0) { return const_cast<float*>(&m_X); }
            else if (index == 1) { return const_cast<float*>(&m_Y); }
            else { return const_cast<float*>(&m_Z); }
        }

        float length() const
        {
            return std::sqrtf( (m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z) );
        }
        float lengthSquared() const 
        {
            return (m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z);
        }

        float dotProduct(const vec3& other) const 
        {
            return (m_X * other.m_X) + (m_Y * other.m_Y) + (m_Z * other.m_Y);
        }
        vec3 crossProduct(const vec3& other) const 
        {
            // Le pruduit vectoriel de u par v est 
            // u x v = [ uY x vZ - uZ x vY, -(uX x vZ - uZ x vX), uX x vY - uY x vX ]

            float x = m_Y * other.m_Z - m_Z * other.m_Y;
            float y = -(m_X * other.m_Z - m_Z * other.m_X);
            float z = m_X * other.m_Y - m_Y * other.m_X;

            return vec3(x, y, z);
        }

        float distance(const vec3& other) const
        {
            return std::sqrtf( (other.m_X - m_X) * (other.m_X - m_X) + (other.m_Y - m_Y) * (other.m_Y - m_Y) +(other.m_Z - m_Z) * (other.m_Z - m_Z) );
        }
        float distanceSquared(const vec3& other) const
        {
            return (other.m_X - m_X) * (other.m_X - m_X) + (other.m_Y - m_Y) * (other.m_Y - m_Y) +(other.m_Z - m_Z) * (other.m_Z - m_Z);
        }


        static float length(const vec3& vec) 
        {
            return std::sqrtf( (vec.m_X * vec.m_X) + (vec.m_Y * vec.m_Y) + (vec.m_Z * vec.m_Z) );
        }
        static float lengthSquared(const vec3 vec)  
        {
            return (vec.m_X * vec.m_X) + (vec.m_Y * vec.m_Y) + (vec.m_Z * vec.m_Z);
        }

        static float dotProduct(const vec3& vec1, const vec3& vec2)  
        {
            return (vec1.m_X * vec2.m_X) + (vec1.m_Y * vec2.m_Y) + (vec1.m_Z * vec2.m_Y);
        }

        static vec3 crossProduct(const vec3& a, const vec3& b)
        {
            // Le pruduit vectoriel de u par v est 
            // u x v = [ uY x vZ - uZ x vY, -(uX x vZ - uZ x vX), uX x vY - uY x vX ]

            float x = a.y() * b.z() - a.z() * b.y();
            float y = -(a.x() * b.z() - a.z() * b.x());
            float z = a.x() * b.y() - a.y() * b.x();

            return vec3(x, y, z);
        }

        static float distance(const vec3& vec1, const vec3& vec2) 
        {
            return std::sqrtf( (vec2.m_X - vec1.m_X) * (vec2.m_X - vec1.m_X) + 
                               (vec2.m_Y - vec1.m_Y) * (vec2.m_Y - vec1.m_Y) +
                               (vec2.m_Z - vec1.m_Z) * (vec2.m_Z - vec1.m_Z) );
        }
        static float distanceSquared(const vec3& vec1, const vec3& vec2) 
        {
            return (vec2.m_X - vec1.m_X) * (vec2.m_X - vec1.m_X) + 
                   (vec2.m_Y - vec1.m_Y) * (vec2.m_Y - vec1.m_Y) +
                   (vec2.m_Z - vec1.m_Z) * (vec2.m_Z - vec1.m_Z);
        }

        // well ..., I don't know what this does (thanks Unity), and I'm not motivated tonigth, I'll fix it tomorrow :)

        static vec3 moveTowards(const vec3& current, const vec3& target, float maxDistance)
        {
            float x = target.m_X - current.m_X;
            float y = target.m_Y - current.m_Y;
            float z = target.m_Z - current.m_Z;

            float distanceSqr = x * x + y * y + z * z;

            if (distanceSqr == 0.0f || (maxDistance >= 0.0f && distanceSqr <= maxDistance * maxDistance))
            {
                return target;
            }

            float distance = std::sqrtf(distanceSqr);

            return vec3(current.m_X + x / distance * maxDistance,
                        current.m_Y + y / distance * maxDistance,
                        current.m_Z + z / distance * maxDistance);

        }


        vec3& normalized()
        {
            float l = this->length();
            if (l > 0.0f) 
            {
                float inverseLength = 1.0f / l;

                m_X *= inverseLength;
                m_Y *= inverseLength;
                m_Z *= inverseLength;
            }

            return *this;
        }

        vec3 getUnitVector() const
        {
            vec3 copy = *this;

            return copy.normalized();
        }

        static vec3 lerp(const vec3& start, const vec3& end, float t)
        {
            t = MathInternal::clamp01(t);

            return vec3(start.x() + (end.x() - start.x()) * t, start.y() + (end.y() - start.y()) * t, start.z() + (end.z() - start.z()) * t);
        }
        static vec3 lerpUnclamped(const vec3& start, const vec3& end, float t)
        {
            return vec3(start.x() + (end.x() - start.x()) * t, start.y() + (end.y() - start.y()) * t, start.z() + (end.z() - start.z()) * t);
        }


        vec3& operator+=(const vec3& other) 
        { 
            this->m_X += other.m_X;
            this->m_Y += other.m_Y;
            this->m_Z += other.m_Z;
            
            return *this; 
        }
        vec3& operator-=(const vec3& other) 
        { 
            this->m_X -= other.m_X;
            this->m_Y -= other.m_Y;
            this->m_Z -= other.m_Z;
            
            return *this; 
        }
        vec3& operator*=(float scalar)
        {
            this->m_X *= scalar;
            this->m_Y *= scalar;
            this->m_Z *= scalar;

            return *this;
        }
        vec3& operator/=(float scalar)
        {
            if (scalar == 0.0f) return *this;

            scalar = 1.0f / scalar;

            this->m_X *= scalar;
            this->m_Y *= scalar;
            this->m_Z *= scalar;

            return *this;
        }

    };

    inline vec3 operator+(const vec3& a, const vec3& b)
    {
        return vec3(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
    }
    inline vec3 operator-(const vec3& a, const vec3& b)
    {
        return vec3(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
    }
    inline vec3 operator*(const vec3& vec, float scalar)
    {
        return vec3(vec.x() * scalar, vec.y() * scalar, vec.z() * scalar);
    }
    inline vec3 operator/(const vec3& vec, float scalar)
    {
        if (scalar == 0.0f) return vec;

        scalar = 1.0f / scalar;

        return vec3(vec.x() * scalar, vec.y() * scalar, vec.z() * scalar);
    }

    inline bool operator==(const vec3& a, const vec3& b)
    {
        return std::abs(a.x() - b.x()) < Constants::Epsilon && 
               std::abs(a.y() - b.y()) < Constants::Epsilon &&
               std::abs(a.z() - b.z()) < Constants::Epsilon;
    }

    inline bool operator!=(const vec3& a, const vec3& b)
    {
        return !(a == b);
    }
}
