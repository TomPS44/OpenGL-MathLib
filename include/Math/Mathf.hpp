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

        inline float clamp(float value, float minInclusive, float maxInclusive) { return MathInternal::clamp(value, minInclusive, maxInclusive); }
        
        inline float clamp01(float value) { return MathInternal::clamp01(value); }

        inline angle clampAngle(const angle& angle, float minDegrees, float maxDegrees)
        {
            return angle::fromDegrees(MathInternal::clamp(angle.asDegrees(), minDegrees, maxDegrees));
        }

        // Simple Absolute Value and Square Root methods, with floats and Angles
        
        inline float abs(float value) { return MathInternal::abs(value); }
        inline float abs(const angle& angle) { return MathInternal::abs(angle.asRadians()); }
        inline float sqrt(float value) { return MathInternal::sqrt(value); }
        

        // All the trigonometry stuff with floats, and Angles, returning floats and Angles

        inline float sin(float value) { return MathInternal::sin(value); }
        inline float cos(float value) { return MathInternal::cos(value); }
        inline float tan(float value) { return MathInternal::tan(value); }

        inline float sin(const angle& angle) { return MathInternal::sin(angle.asRadians()); }
        inline float cos(const angle& angle) { return MathInternal::cos(angle.asRadians()); }
        inline float tan(const angle& angle) { return MathInternal::tan(angle.asRadians()); }

        inline float asin(float value) { return MathInternal::asin(value); }
        inline float acos(float value) { return MathInternal::acos(value); }
        inline float atan(float value) { return MathInternal::atan(value); }
        inline float atan2(float y, float x) { return MathInternal::atan2(y, x); }

        inline angle asinAngle(float value) { return angle::fromRadians(MathInternal::asin(value)); }
        inline angle acosAngle(float value) { return angle::fromRadians(MathInternal::acos(value)); }
        inline angle atanAngle(float value) { return angle::fromRadians(MathInternal::atan(value)); }
        inline angle atan2Angle(float y, float x) { return angle::fromRadians(MathInternal::atan2(y, x)); }

        // Just a Lerp method, which will be defined in each struct Vec, Angle... seperatly

        inline float lerp(float start, float end, float t) { return MathInternal::lerp(start, end, t); }

        inline float mod(float value, float modulus) { return MathInternal::mod(value, modulus); }

        inline float pow(float value, float exponent) { return MathInternal::pow(value, exponent); }

        inline bool nearlyEqual(float a, float b) { return MathInternal::nearlyEqual(a, b); }


        // Min and Max methods, taking two or an infinite number of arguments 

        template<typename T>
        T max(T a, T b) { return MathInternal::max(a, b); }

        template<typename T>
        T min(T a, T b) { return MathInternal::min(a, b); }

        template<typename T, typename... Args>
        T max(T first, Args... args) { return MathInternal::max(first, args...); }

        template<typename T, typename... Args>
        T min(T first, Args... args) { return MathInternal::min(first, args...); }
    }
}