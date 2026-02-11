#pragma once
#include <cmath>

#include "Math\Concepts.hpp"

namespace math
{
   
    // Min and Max methods, taking two or an infinite number of arguments 
    template<IsComparable T>
    T max(T a, T b) 
    {
        return a > b ? a : b;
    }
    template<IsComparable T>
    T min(T a, T b) 
    {
        return a < b ? a : b;
    }

    template<IsComparable T, IsComparable... Args>
    T max(T first, Args... args) 
    {
        T result = first;
        ((result = max(result, args)), ...); 
        return result;
    }
    template<IsComparable T, IsComparable... Args>
    T mMin(T first, Args... args) 
    {
        T result = first;
        ((result = min(result, args)), ...); 
        return result;
    }


    // Methods to clamp a float or an Angle between two numbers

    template<Number N>
    inline N clamp(N value, N minInclusive, N maxInclusive)
    {
        if (value < minInclusive) value = minInclusive;
        else if (value > maxInclusive) value = maxInclusive;

        return value;
    }
    template<Number N>
    inline N clamp01(N value)
    {
        return clamp(value, static_cast<N>(0.0), static_cast<N>(1.0));
    }


    // Simple Absolute Value and Square Root methods, with floats and Angles

    template<Number N>
    inline N abs(N value) { return std::abs(value); }
    template<std::floating_point F>
    inline F sqrt(float value) { return static_cast<F>(std::sqrt(value)); }
    
    // All the trigonometry stuff with floats, and Angles, returning floats and Angles

    template<std::floating_point F>
    inline F sin(F value) { return static_cast<F>(std::sin(value)); }
    template<std::floating_point F>
    inline F cos(F value) { return static_cast<F>(std::cos(value)); }
    template<std::floating_point F>
    inline float tan(float value) { return static_cast<F>(std::tan(value)); }
    template<std::floating_point F>
    inline F asin(F value) { return static_cast<F>(std::asin(value)); }
    template<std::floating_point F>
    inline F acos(F value) { return static_cast<F>(std::acos(value)); }
    template<std::floating_point F>
    inline F atan(F value) { return static_cast<F>(std::atan(value)); }
    template<std::floating_point F>
    inline F atan2(F y, F x) { return static_cast<F>(std::atan2(y, x)); }

    // Just a Lerp method, which will be defined in each struct Vec, Angle... seperatly

    template<Number N>
    inline N lerp(N start, N end, N t)
    {
        return start + (end - start) * clamp01(t);
    }

    template<Number N>
    inline N mod(N value, N modulus)
    {
        return static_cast<N>(std::fmod(value, modulus));
    }

    template<Number N>
    inline N pow(N value, N exponent)
    {
        return static_cast<N>(std::pow(value, exponent));
    }

    template<Number N>
    inline N toRadians(N degAngle)
    {
        return degAngle * static_cast<N>(0.0174532925);
    }

    template<Number N>
    inline N toDegrees(N radAngle)
    {
        return radAngle * static_cast<N>(57.295779513);
    }



    template<Number N>
    inline N pi()
    {
        return static_cast<N>(std::numbers::pi);
    }
    template<Number N>
    inline N twoPi()
    {
        return static_cast<N>(std::numbers::pi * 2.0);
    }
    template<Number N>
    inline N e()
    {
        return static_cast<N>(std::numbers::e);
    }
    template<Number N>
    inline N degToRad()
    {
        return static_cast<N>(0.0174532925);
    }
    template<Number N>
    inline N radToDeg()
    {
        return static_cast<N>(57.295779513);
    }
    template<Number N>
    inline N sqrtOf2()
    {
        return static_cast<N>(std::numbers::sqrt2);
    }
    template<Number N>
    inline N sqrtOf3()
    {
        return static_cast<N>(std::numbers::sqrt3);
    }
    template<Number N>
    inline N epsilon()
    {
        return static_cast<N>(0.1e+06);
    }

    template<std::floating_point F>
    inline bool nearlyEqual(F lhs, F rhs)
    {
        return std::abs(rhs - lhs) < static_cast<F>(0.1e+06);
    }
    
}