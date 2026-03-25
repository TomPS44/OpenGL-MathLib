#pragma once

#include <concepts>
#include <type_traits>

namespace glMath
{
    // The concept Number allows all the types that are the same as 
    // int, float, double, long, long long, long double
    template<typename T>
    concept Number = 
        std::is_same_v<T, int>         ||
        std::is_same_v<T, float>       ||
        std::is_same_v<T, double>      ||
        std::is_same_v<T, long>        ||
        std::is_same_v<T, long long>   ||
        std::is_same_v<T, long double> ;

    // The concept FloatingNumber allow all the types that are the same as
    // float, double
    template<typename T>
    concept FloatingNumber = 
        std::is_same_v<T, float>  ||
        std::is_same_v<T, double> ;

    // The concept Comparable allows all the types that define the operators 
    // < , >, <=, >= , == , !=
    template<typename T>
    concept Comparable =
        requires (T a, T b)
        {
            a > b;
            a >= b;
            a < b;
            a <= b;
            a == b;
            a != b;
        };

    // The concept IntegralNumber allows all the types that are the same as 
    // int, long, (these 2 are the same), long long, int8_t, int16_t, int32_t, int64_t
    template<typename T>
    concept IntegralNumber = 
        std::is_same_v<T, int>       ||
        std::is_same_v<T, long>      ||
        std::is_same_v<T, long long> ||
        std::is_same_v<T, int8_t>    ||
        std::is_same_v<T, int16_t>   ||
        std::is_same_v<T, int32_t>   ||
        std::is_same_v<T, int64_t>   ;

}