#pragma once

#include "Math\Constants.hpp"
#include "Math\MathInternal.hpp"

namespace Mathematics
{
    struct Angle
    {
    private:
        float m_Radians;

        explicit Angle(float inRad) : m_Radians(inRad) {}

    public: 
        // Constructors

        static Angle FromRadians(float angle) { return Angle(angle); } 
        static Angle FromDegrees(float angle) { return Angle(angle * Constants::DegToRad); }

        // Getters

        float AsDegrees() const { return m_Radians * Constants::RadToDeg; }
        float AsRadians() const { return m_Radians; }


        Angle& Normalize()
        {
            m_Radians = MathInternal::Mod(m_Radians, 2.0f * Constants::PI);
            if (m_Radians < 0) m_Radians += 2.0f * Constants::PI;
            return *this;
        }

        // Lerp Methods

        static inline Angle Lerp(float startDeg, float endDeg, float t)
        {
            return Angle::FromDegrees(MathInternal::Lerp(startDeg, endDeg, t));
        }

        static inline Angle Lerp(const Angle& start, const Angle& end, float t)
        {
            return Angle::FromRadians(MathInternal::Lerp(start.AsRadians(), end.AsRadians(), MathInternal::Clamp01(t)));
        }

        static inline Angle ShortLerp(float startDeg, float endDeg, float t)
        {
            float delta = Angle::FromDegrees(endDeg).AsRadians() - Angle::FromDegrees(startDeg).AsRadians();

            float fullCircle = 2.0f * Constants::PI;
            delta = MathInternal::Mod(delta, fullCircle);

            if (delta > Constants::PI) delta -= fullCircle;
            if (delta < -Constants::PI) delta += fullCircle;

            // On peut utiliser Mathf sans erreur
            return Angle::FromRadians(Angle::FromDegrees(startDeg).AsRadians() + delta * MathInternal::Clamp01(t));
        }

        static inline Angle ShortLerp(const Angle& start, const Angle& end, float t) 
        {
            float delta = end.AsRadians() - start.AsRadians();

            float fullCircle = 2.0f * Constants::PI;
            delta = MathInternal::Mod(delta, fullCircle);

            if (delta > Constants::PI) delta -= fullCircle;
            if (delta < -Constants::PI) delta += fullCircle;

            // On peut utiliser Mathf sans erreur
            return Angle::FromRadians(start.AsRadians() + delta * MathInternal::Clamp01(t));
        }

        // Reference Operators

        Angle& operator+=(const Angle& other)
        {
            m_Radians += other.AsRadians();
            return *this;
        }
        Angle& operator-=(const Angle& other)
        {
            m_Radians -= other.AsRadians();
            return *this;
        }
        Angle& operator*=(float scalar)
        {
            m_Radians *= scalar;
            return *this;
        }
        Angle& operator/=(float scalar)
        {
            if (scalar == 0) return *this;

            m_Radians /= scalar;
            return *this;
        }

    };

    // Arithmetic Operators

    inline Angle operator+(const Angle& a, const Angle& b) 
    {
        return Angle::FromRadians(a.AsRadians() + b.AsRadians());
    }
    inline Angle operator-(const Angle& a, const Angle& b) 
    {
        return Angle::FromRadians(a.AsRadians() - b.AsRadians());
    }
    inline Angle operator*(const Angle& a, float scalar) 
    {
        return Angle::FromRadians(a.AsRadians() * scalar);
    }
    inline Angle operator/(const Angle& a, float scalar) 
    {
        return Angle::FromRadians(a.AsRadians() / scalar);
    }

    inline bool operator>(const Angle& a, const Angle& b) 
    {
        return a.AsRadians() > b.AsRadians();
    }
    inline bool operator<(const Angle& a, const Angle& b) 
    {
        return a.AsRadians() < b.AsRadians();
    }

    inline bool operator==(const Angle& a, const Angle& b)
    {
        return MathInternal::Abs(a.AsRadians() - b.AsRadians()) < Constants::Epsilon;
    }
    inline bool operator!=(const Angle& a, const Angle& b)
    {
        return !(a == b);
    }

    // User-literals operators

    inline Angle operator"" _deg(long double d) 
    {
        return Angle::FromDegrees(static_cast<float>(d));
    }
    inline Angle operator"" _rad(long double d) 
    {
        return Angle::FromRadians(static_cast<float>(d));
    }

    
}

