#include <iostream>
#include <concepts>

#include "Math.hpp"

template<std::floating_point F>
void logVec2(const vec2<F>& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ")" << std::endl;
}
template<std::floating_point F>
void logVec3(const vec3<F>& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
}
template<std::floating_point F>
void logQuat(const quat<F>& quat)
{
    std::cout << "(" << quat.w << ", " << quat.x << ", " << quat.y << ", " << quat.z << ")" << std::endl;
}
void logMat4(const mat4& mat)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << mat.columns[j][i] << " ";
        }
        std::cout << '\n';
    }
}


int main() 
{
    // It's just a way of writing vec3(1.0, 1.0, 1.0) 
    logVec3(vec3d::lerp(vec3f::zero<float>().XYZ<double>(), vec3d::one<double>() * 2.0, 0.5));

    logMat4(quatd::identity().toMat4());

    return 0;
}



// super cool namespace color : #E6DD9A