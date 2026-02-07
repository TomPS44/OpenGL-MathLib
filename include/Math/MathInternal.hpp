#pragma once
#include <cmath>

#include "Math\Angle.hpp"

namespace Mathematics
{
    // TODO: change all the functions case to camleCase instead of PascalCase

    namespace MathInternal
    {
        // Min and Max methods, taking two or an infinite number of arguments 

        template<typename T>
        T max(T a, T b) 
        {
            return a > b ? a : b;
        }
        template<typename T>
        T min(T a, T b) 
        {
            return a < b ? a : b;
        }

        template<typename T, typename... Args>
        T max(T first, Args... args) 
        {
            T result = first;
            ((result = max(result, args)), ...); 
            return result;
        }
        template<typename T, typename... Args>
        T mMin(T first, Args... args) 
        {
            T result = first;
            ((result = min(result, args)), ...); 
            return result;
        }

        // Methods to clamp a float or an Angle between two numbers

        inline float clamp(float value, float minInclusive, float maxInclusive)
        {
            // si value = 25, min = 10, et max = 20, Max(10, Min(25, 20)) -> Max(10, 20) -> 20, et c'est bon :) !
            return max(minInclusive, min(value, maxInclusive));
        }
        inline float clamp01(float value)
        {
            return clamp(value, 0.0f, 1.0f);
        }

        // Simple Absolute Value and Square Root methods, with floats and Angles
        
        inline float abs(float value) { return std::abs(value); }
        inline float sqrt(float value) { return std::sqrtf(value); }
        
        // All the trigonometry stuff with floats, and Angles, returning floats and Angles

        inline float sin(float value) { return std::sinf(value); }
        inline float cos(float value) { return std::cosf(value); }
        inline float tan(float value) { return std::tanf(value); }

        inline float asin(float value) { return std::asinf(value); }
        inline float acos(float value) { return std::acosf(value); }
        inline float atan(float value) { return std::atanf(value); }
        inline float atan2(float y, float x) { return std::atan2f(y, x); }

        // Just a Lerp method, which will be defined in each struct Vec, Angle... seperatly

        inline float lerp(float start, float end, float t)
        {
            return start + (end - start) * clamp01(t);
        }

        inline float mod(float value, float modulus)
        {
            return std::fmod(value, modulus);
        }

        inline float pow(float value, float exponent)
        {
            return std::powf(value, exponent);
        }

        inline float toRadians(float degAngle)
        {
            return degAngle * Constants::DegToRad;
        }

        inline float toDegrees(float radAngle)
        {
            return radAngle * Constants::RadToDeg;
        }

        inline bool nearlyEqual(float lhs, float rhs)
        {
            return std::abs(rhs - lhs) < Constants::Epsilon;;
        }
    }
}