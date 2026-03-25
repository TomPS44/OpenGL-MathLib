#include <iostream>
#include <iomanip> 

#include <random>


#include "Quaternions.hpp"
#include "Vectors.hpp"
#include "IntVectors.hpp"
#include "Matrices.hpp"



template<glMath::FloatingNumber F>
void logVec2(const glMath::vec2<F>& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ")" << std::endl;
}
template<glMath::IntegralNumber I>
void logIntVec2(const glMath::iVec2<I>& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ")" << std::endl;
}

template<glMath::FloatingNumber F>
void logVec3(const glMath::vec3<F>& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
}

template<glMath::IntegralNumber I>
void logIntVec3(const glMath::iVec3<I>& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
}
template<glMath::FloatingNumber F>
void logVec4(const glMath::vec4<F>& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")" << std::endl;
}
template<glMath::FloatingNumber F>
void logQuat(const glMath::quat<F>& quat)
{
    std::cout << "(" << quat.w << ", " << quat.x << ", " << quat.y << ", " << quat.z << ")" << std::endl;
}
template<glMath::FloatingNumber F>
void logDualQuat(const glMath::dualQuat<F>& dQuat)
{
    std::cout << "(" << dQuat.real.w << ", " << dQuat.real.x << ", " << dQuat.real.y << ", " << dQuat.real.z << " | " << 
                 dQuat.dual.w << ", " << dQuat.dual.x << ", " << dQuat.dual.y << ", " << dQuat.dual.z << ")" << std::endl;
}

template<glMath::FloatingNumber F>
void logMat4(const glMath::mat4<F>& mat)
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

template<glMath::FloatingNumber F>
void logMat3(const glMath::mat3<F>& mat)
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
template<glMath::FloatingNumber F>
void logMat2(const glMath::mat2<F>& mat)
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
    // std::cout << std::setprecision(30);

    std::cout << vec2f::angleBetween(vec2f(1, 0), vec2f::fromAngle(90.0f)) << '\n';


    // glMath::iVec2<int32_t> vec(12, 13);

    // logIntVec2(vec);

    logVec2(vec2f(2.0f, 1.0f).normalize());

    logVec2(vec2d::slerpUnclamped(vec2d::fromAngle(45.0f).projectOnto(vec2f(2.0f, 8.0f).as<double>()) * vec2d::crossProduct(vec2d::dotProduct(vec2d::one(), vec2d::right()) * vec2d::up(), vec2d::min(vec2d::up(), vec2d::left())) * vec2d::distanceSquared(vec2d::left() * vec2d::right(), vec2d::fromAngle(-365.0)), vec2f::fromAngle(5764.0f).as<double>() * vec2d::dotProduct(vec2d(2567.56, 15.78), vec2d::one()), 0.75));

    return 0;
}



// super cool namespace color : #E6DD9A

// #1e1e1e
// #d4d4d4
// #3498db

// #ffffff
// #202020
// #005fd8 