#include <iostream>

#include <algorithm>

#include <unordered_map> 
#include <unordered_set> 


#include "Quaternions.hpp"
#include "Vectors.hpp"
#include "IntVectors.hpp"
#include "Matrices.hpp"



template<glMath::FloatingNumber F>
void logVec2(const vec2<F>& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ")" << std::endl;
}
template<IntegralNumber I>
void logIntVec2(const iVec2<I>& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ")" << std::endl;
}
template<glMath::FloatingNumber F>
void logVec3(const vec3<F>& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
}
void logIntVec3(const intVec3& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
}
template<glMath::FloatingNumber F>
void logVec4(const vec4<F>& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")" << std::endl;
}
template<glMath::FloatingNumber F>
void logQuat(const quat<F>& quat)
{
    std::cout << "(" << quat.w << ", " << quat.x << ", " << quat.y << ", " << quat.z << ")" << std::endl;
}
template<glMath::FloatingNumber F>
void logDualQuat(const dualQuat<F>& dQuat)
{
    std::cout << "(" << dQuat.real.w << ", " << dQuat.real.x << ", " << dQuat.real.y << ", " << dQuat.real.z << " | " << 
                 dQuat.dual.w << ", " << dQuat.dual.x << ", " << dQuat.dual.y << ", " << dQuat.dual.z << ")" << std::endl;
}
template<FloatingNumber F>
void logMat4(const mat4<F>& mat)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            F value = mat.columns[j][i];
            if ( std::abs(value) > static_cast<F>(1e-06) ) std::cout << value << " ";
            else std::cout << "0" << " ";
        }

        std::cout << '\n';
    }
}
template<FloatingNumber F>
void logMat3(const mat3<F>& mat)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            F value = mat.columns[j][i];
            if ( std::abs(value) > static_cast<F>(1e-06) ) std::cout << value << " ";
            else std::cout << "0" << " ";
        }

        std::cout << '\n';
    }
}
template<FloatingNumber F>
void logMat2(const mat2<F>& mat)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            F value = mat.columns[j][i];
            if ( std::abs(value) > static_cast<F>(1e-06) ) std::cout << value << " ";
            else std::cout << "0" << " ";
        }

        std::cout << '\n';
    }
    std::cout << "" << std::endl;
}




int main() 
{
    vec2f fPos(526.9f, 15.2f);

    logIntVec2(fPos.floorTo<int>());

    // std::cout << INT32_MAX << '\n';
    // std::cout << static_cast<float>(std::numeric_limits<int>().max());


    // std::cout << std::clamp(std::floor(15276865473.9f), static_cast<float>(std::numeric_limits<int>().lowest()), static_cast<float>(std::numeric_limits<int>().max()));
    
    


    return 0;
}



// super cool namespace color : #E6DD9A

// #1e1e1e
// #d4d4d4
// #3498db

// #ffffff
// #202020
// #005fd8 