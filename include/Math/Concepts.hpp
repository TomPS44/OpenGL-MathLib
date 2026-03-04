#pragma once

#include <concepts>
#include <type_traits>

namespace math
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

    // The concept IsComparable encapsulates all the types that define the operators 
    // < , > , == , !=
    template<typename T>
    concept IsComparable =
        requires (T a, T b)
        {
            a > b;
            a < b;
            a == b;
            a != b;
        };
    
}