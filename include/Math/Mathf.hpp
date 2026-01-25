#pragma once
#include <cmath>

#include "Math\Angle.hpp"

namespace Mathematics
{
    namespace Mathf
    {
        // Constants, coming from the namespace Mathematics::Constants

        static constexpr float PI = Constants::PI;
        static constexpr float E = Constants::E;
        static constexpr float DegToRad = Constants::DegToRad; 
        static constexpr float RadToDeg = Constants::RadToDeg;
        static constexpr float Epsilon = Constants::Epsilon;

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
        inline Angle ClampAngle(const Angle& angle, float minDegrees, float maxDegrees)
        {
            // si value = 25, min = 10, et max = 20, Max(10, Min(25, 20)) -> Max(10, 20) -> 20, et c'est bon :) !
            return Angle::FromDegrees((minDegrees, Min(angle.AsDegrees(), maxDegrees)));
        }

        // Simple Absolute Value and Square Root methods, with floats and Angles
        
        inline float Abs(float value) { return std::abs(value); }
        inline float Abs(const Angle& angle) { return std::abs(angle.AsRadians()); }
        inline float Sqrt(float value) { return std::sqrtf(value); }
        
        // All the trigonometry stuff with floats, and Angles, returning floats and Angles

        inline float Sin(float value) { return std::sinf(value); }
        inline float Cos(float value) { return std::cosf(value); }
        inline float Tan(float value) { return std::tanf(value); }

        inline float Sin(const Angle& angle) { return std::sinf(angle.AsRadians()); }
        inline float Cos(const Angle& angle) { return std::cosf(angle.AsRadians()); }
        inline float Tan(const Angle& angle) { return std::tanf(angle.AsRadians()); }

        inline float Asin(float value) { return std::asinf(value); }
        inline float Acos(float value) { return std::acosf(value); }
        inline float Atan(float value) { return std::atanf(value); }
        inline float Atan2(float y, float x) { return std::atan2f(y, x); }

        inline Angle AsinAngle(float value) { return Angle::FromRadians(std::asinf(value)); }
        inline Angle AcosAngle(float value) { return Angle::FromRadians(std::acosf(value)); }
        inline Angle AtanAngle(float value) { return Angle::FromRadians(std::atanf(value)); }
        inline Angle Atan2Angle(float y, float x) { return Angle::FromRadians(std::atan2f(y, x)); }

        // Just a Lerp method, which will be defined in each struct Vec, Angle... seperatly

        inline float Lerp(float start, float end, float t)
        {
            t = Clamp01(t);
            return start + t * (end - start);
        }
    }
}