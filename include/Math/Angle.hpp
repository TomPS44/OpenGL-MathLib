#pragma once

#include <cmath>
#include <concepts>

#include "Math\MathInternal.hpp"
#include "Math\Concepts.hpp"

namespace math
{
    template<std::floating_point F>
    struct vec2;

    template<std::floating_point F>
    struct angle
    {
    private:
        F m_Radians;

        explicit angle(F inRad) : m_Radians(inRad) {}

    public: 
        // Constructors

        // Returns an angle from the specified DEGREES
        static angle fromRadians(F rad) { return angle(rad); } 
        // Returns an angle from the specified RADIANS
        static angle fromDegrees(F deg) { return angle(deg * math::degToRad<F>()); }

        // Getters

        F asDegrees() const { return m_Radians * math::radToDeg<F>(); }
        F asRadians() const { return m_Radians; }


        angle& normalize()
        {
            m_Radians = static_cast<F>(std::fmod(m_Radians, math::twoPi<F>()));
            if (m_Radians < 0) m_Radians += math::twoPi<F>();
            return *this;
        }

        static inline angle angleBetween(const vec2<F>& a, const vec2<F>& b);

        // Lerp Methods

        // Linearly interpolates between two DEGREES
        static inline angle lerp(F startDeg, F endDeg, F t)
        {
            t = math::clamp01(t);
            return angle::fromDegrees(math::lerp(startDeg, endDeg, t));
        }

        static inline angle lerp(const angle& start, const angle& end, F t)
        {
            t = clamp01(t);
            return angle::fromRadians(math::lerp(start.asRadians(), end.asRadians(), clamp01(t)));
        }

        // Linearly interpolates between two DEGREES, by taking the shortest path
        static inline angle shortLerp(F startDeg, F endDeg, F t)
        {
            return shortLerp(angle::fromDegrees(startDeg), angle::fromDegrees(endDeg), t);
        }

        static inline angle shortLerp(const angle& start, const angle& end, float t) 
        {
            F s = start.asRadians();
            F e = end.asRadians();

            t = math::clamp01(t);
            F delta = static_cast<F>(std::fmod(e - s, math::twoPi<F>()));

            F fullCircle = math::twoPi<F>();
            delta = static_cast<F>(std::fmod(delta, fullCircle));

            if (delta > math::pi<F>()) delta -= fullCircle;
            if (delta < -math::pi<F>()) delta += fullCircle;

            // On peut utiliser Mathf sans erreur
            return angle::fromRadians(s + delta * clamp01(t));
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

    template<std::floating_point F>
    inline angle<F> operator+(const angle<F>& a, const angle<F>& b) 
    {
        return angle<F>::fromRadians(a.asRadians() + b.asRadians());
    }
    template<std::floating_point F>
    inline angle<F> operator-(const angle<F>& a, const angle<F>& b) 
    {
        return angle<F>::fromRadians(a.asRadians() - b.asRadians());
    }
    template<std::floating_point F>
    inline angle<F> operator*(const angle<F>& ang, F scalar) 
    {
        return angle<F>::fromRadians(ang.asRadians() * scalar);
    }
    template<std::floating_point F>
    inline angle<F> operator*(F scalar, const angle<F>& ang) 
    {
        return angle<F>::fromRadians(ang.asRadians() * scalar);
    }
    template<std::floating_point F>
    inline angle<F> operator/(const angle<F>& ang, F scalar) 
    {
        if (scalar == static_cast<F>(0.0)) return ang;

        return angle<F>::fromRadians(ang.asRadians() / scalar);
    }

    template<std::floating_point F>
    inline bool operator>(const angle<F>& a, const angle<F>& b) 
    {
        return a.asRadians() > b.asRadians();
    }
    template<std::floating_point F>
    inline bool operator<(const angle<F>& a, const angle<F>& b) 
    {
        return a.asRadians() < b.asRadians();
    }

    template<std::floating_point F>
    inline bool operator==(const angle<F>& a, const angle<F>& b)
    {
        return static_cast<F>(std::abs(a.asRadians() - b.asRadians())) < math::epsilon<F>();
    }
    template<std::floating_point F>
    inline bool operator!=(const angle<F>& a, const angle<F>& b)
    {
        return !(a == b);
    }

    

    
}

