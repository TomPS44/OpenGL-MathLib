#pragma once

#include "Math\Angle.hpp"
#include "Math\MathInternal.hpp"

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
        

        // Methods to clamp a float or an Angle between two numbers

        inline float Clamp(float value, float minInclusive, float maxInclusive) { return MathInternal::Clamp(value, minInclusive, maxInclusive); }
        
        inline float Clamp01(float value) { return MathInternal::Clamp01(value); }

        inline Angle ClampAngle(const Angle& angle, float minDegrees, float maxDegrees)
        {
            return Angle::FromDegrees(MathInternal::Clamp(angle.AsDegrees(), minDegrees, maxDegrees));
        }

        // Simple Absolute Value and Square Root methods, with floats and Angles
        
        inline float Abs(float value) { return MathInternal::Abs(value); }
        inline float Abs(const Angle& angle) { return MathInternal::Abs(angle.AsRadians()); }
        inline float Sqrt(float value) { return MathInternal::Sqrt(value); }
        

        // All the trigonometry stuff with floats, and Angles, returning floats and Angles

        inline float Sin(float value) { return MathInternal::Sin(value); }
        inline float Cos(float value) { return MathInternal::Cos(value); }
        inline float Tan(float value) { return MathInternal::Tan(value); }

        inline float Sin(const Angle& angle) { return MathInternal::Sin(angle.AsRadians()); }
        inline float Cos(const Angle& angle) { return MathInternal::Cos(angle.AsRadians()); }
        inline float Tan(const Angle& angle) { return MathInternal::Tan(angle.AsRadians()); }

        inline float Asin(float value) { return MathInternal::Asin(value); }
        inline float Acos(float value) { return MathInternal::Acos(value); }
        inline float Atan(float value) { return MathInternal::Atan(value); }
        inline float Atan2(float y, float x) { return MathInternal::Atan2(y, x); }

        inline Angle AsinAngle(float value) { return Angle::FromRadians(MathInternal::Asin(value)); }
        inline Angle AcosAngle(float value) { return Angle::FromRadians(MathInternal::Acos(value)); }
        inline Angle AtanAngle(float value) { return Angle::FromRadians(MathInternal::Atan(value)); }
        inline Angle Atan2Angle(float y, float x) { return Angle::FromRadians(MathInternal::Atan2(y, x)); }

        // Just a Lerp method, which will be defined in each struct Vec, Angle... seperatly

        inline float Lerp(float start, float end, float t) { return MathInternal::Lerp(start, end, t); }

        inline float Mod(float value, float modulus) { return MathInternal::Mod(value, modulus); }

        inline float Pow(float value, float exponent) { return MathInternal::Pow(value, exponent); }


        // Min and Max methods, taking two or an infinite number of arguments 

        template<typename T>
        T Max(T a, T b) { return MathInternal::Max(a, b); }

        template<typename T>
        T Min(T a, T b) { return MathInternal::Min(a, b); }

        template<typename T, typename... Args>
        T Max(T first, Args... args) { return MathInternal::Max(first, args...); }

        template<typename T, typename... Args>
        T Min(T first, Args... args) { return MathInternal::Min(first, args...); }
    }
}