#pragma once

#include <concepts>

namespace math
{
    // The concept Number encapsulates all the types that are the same as 
    // int, float, double, long, long long, long double
    template<typename T>
    concept Number = 
        std::is_same_v<T, int>         ||
        std::is_same_v<T, float>       ||
        std::is_same_v<T, double>      ||
        std::is_same_v<T, long>        ||
        std::is_same_v<T, long long>   ||
        std::is_same_v<T, long double>;

    // The concept Number encapsulates all the types that define the operators 
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