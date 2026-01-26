#pragma once
#include <cmath>

#include "Math\Angle.hpp"

namespace Mathematics
{
    namespace MathInternal
    {
        // Min and Max methods, taking two or an infinite number of arguments 

        template<typename T>
        T Max(T a, T b) 
        {
            return a > b ? a : b;
        }
        template<typename T>
        T Min(T a, T b) 
        {
            return a < b ? a : b;
        }

        template<typename T, typename... Args>
        T Max(T first, Args... args) 
        {
            T result = first;
            ((result = Max(result, args)), ...); 
            return result;
        }
        template<typename T, typename... Args>
        T Min(T first, Args... args) 
        {
            T result = first;
            ((result = Min(result, args)), ...); 
            return result;
        }

        // Methods to clamp a float or an Angle between two numbers

        inline float Clamp(float value, float minInclusive, float maxInclusive)
        {
            // si value = 25, min = 10, et max = 20, Max(10, Min(25, 20)) -> Max(10, 20) -> 20, et c'est bon :) !
            return Max(minInclusive, Min(value, maxInclusive));
        }
        inline float Clamp01(float value)
        {
            return Clamp(value, 0.0f, 1.0f);
        }

        // Simple Absolute Value and Square Root methods, with floats and Angles
        
        inline float Abs(float value) { return std::abs(value); }
        inline float Sqrt(float value) { return std::sqrtf(value); }
        
        // All the trigonometry stuff with floats, and Angles, returning floats and Angles

        inline float Sin(float value) { return std::sinf(value); }
        inline float Cos(float value) { return std::cosf(value); }
        inline float Tan(float value) { return std::tanf(value); }

        inline float Asin(float value) { return std::asinf(value); }
        inline float Acos(float value) { return std::acosf(value); }
        inline float Atan(float value) { return std::atanf(value); }
        inline float Atan2(float y, float x) { return std::atan2f(y, x); }

        // Just a Lerp method, which will be defined in each struct Vec, Angle... seperatly

        inline float Lerp(float start, float end, float t)
        {
            t = Clamp01(t);
            return start + t * (end - start);
        }

        inline float Mod(float value, float modulus)
        {
            return std::fmodf(value, modulus);
        }

        inline float Pow(float value, float exponent)
        {
            return std::powf(value, exponent);
        }
    }
}