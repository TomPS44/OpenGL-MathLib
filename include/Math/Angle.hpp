#pragma once

#include <cmath>

#include "Math\Constants.hpp"
#include "Math\MathInternal.hpp"

namespace Mathematics
{
    struct vec2;

    struct angle
    {
    private:
        float m_Radians;

        explicit angle(float inRad) : m_Radians(inRad) {}

    public: 
        // Constructors

        // Returns an angle from the specifief DEGREES
        static angle fromRadians(float rad) { return angle(rad); } 
        // Returns an angle from the specified RADIANS
        static angle fromDegrees(float deg) { return angle(deg * Constants::DegToRad); }

        // Getters

        float asDegrees() const { return m_Radians * Constants::RadToDeg; }
        float asRadians() const { return m_Radians; }


        angle& normalize()
        {
            m_Radians = MathInternal::mod(m_Radians, 2.0f * Constants::PI);
            if (m_Radians < 0) m_Radians += 2.0f * Constants::PI;
            return *this;
        }

        static inline angle angleBetween(const vec2& a, const vec2& b);

        // Lerp Methods

        // Linearly interpolates between two DEGREES
        static inline angle lerp(float startDeg, float endDeg, float t)
        {
            t = MathInternal::clamp01(t);
            return angle::fromDegrees(MathInternal::lerp(startDeg, endDeg, t));
        }

        static inline angle lerp(const angle& start, const angle& end, float t)
        {
            t = MathInternal::clamp01(t);
            return angle::fromRadians(MathInternal::lerp(start.asRadians(), end.asRadians(), MathInternal::clamp01(t)));
        }

        // Linearly interpolates between two DEGREES, by taking the shortest path
        static inline angle shortLerp(float startDeg, float endDeg, float t)
        {
            return shortLerp(angle::fromDegrees(startDeg), angle::fromDegrees(endDeg), t);
        }

        static inline angle shortLerp(const angle& start, const angle& end, float t) 
        {
            float s = start.asRadians();
            float e = end.asRadians();

            t = MathInternal::clamp01(t);
            float delta = MathInternal::mod(e - s, 2.0f * Constants::PI);

            float fullCircle = 2.0f * Constants::PI;
            delta = MathInternal::mod(delta, fullCircle);

            if (delta > Constants::PI) delta -= fullCircle;
            if (delta < -Constants::PI) delta += fullCircle;

            // On peut utiliser Mathf sans erreur
            return angle::fromRadians(s + delta * MathInternal::clamp01(t));
        }


        // Reference Operators

        angle& operator+=(const angle& other)
        {
            m_Radians += other.asRadians();
            return *this;
        }
        angle& operator-=(const angle& other)
        {
            m_Radians -= other.asRadians();
            return *this;
        }
        angle& operator*=(float scalar)
        {
            m_Radians *= scalar;
            return *this;
        }
        angle& operator/=(float scalar)
        {
            if (scalar == 0) return *this;

            m_Radians /= scalar;
            return *this;
        }

    };

    // Arithmetic Operators

    inline angle operator+(const angle& a, const angle& b) 
    {
        return angle::fromRadians(a.asRadians() + b.asRadians());
    }
    inline angle operator-(const angle& a, const angle& b) 
    {
        return angle::fromRadians(a.asRadians() - b.asRadians());
    }
    inline angle operator*(const angle& angle, float scalar) 
    {
        return angle::fromRadians(angle.asRadians() * scalar);
    }
    inline angle operator/(const angle& angle, float scalar) 
    {
        if (scalar == 0.0f) return angle;

        return angle::fromRadians(angle.asRadians() / scalar);
    }

    inline bool operator>(const angle& a, const angle& b) 
    {
        return a.asRadians() > b.asRadians();
    }
    inline bool operator<(const angle& a, const angle& b) 
    {
        return a.asRadians() < b.asRadians();
    }

    inline bool operator==(const angle& a, const angle& b)
    {
        return MathInternal::abs(a.asRadians() - b.asRadians()) < Constants::Epsilon;
    }
    inline bool operator!=(const angle& a, const angle& b)
    {
        return !(a == b);
    }

    // User-literals operators

    inline angle operator"" _deg(long double d) 
    {
        return angle::fromDegrees(static_cast<float>(d));
    }
    inline angle operator"" _rad(long double d) 
    {
        return angle::fromRadians(static_cast<float>(d));
    }

    
}

