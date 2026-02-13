#include <iostream>
#include <concepts>

// #include "Math.hpp"
#include "Vectors.hpp"

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
// template<std::floating_point F>
// void logQuat(const quat<F>& quat)
// {
//     std::cout << "(" << quat.w << ", " << quat.x << ", " << quat.y << ", " << quat.z << ")" << std::endl;
// }
// void logMat4(const mat4& mat)
// {
//     for (int i = 0; i < 4; i++)
//     {
//         for (int j = 0; j < 4; j++)
//         {
//             std::cout << mat.columns[j][i] << " ";
//         }
//         std::cout << '\n';
//     }
// }


int main() 
{
    // It's just a way of writing vec3(1.0, 1.0, 1.0) 
    logVec3(vec3d::lerp(vec3f::zero().XYZ<double>(), vec3d::one() * 2.0, 0.5));
    logVec3(vec3d::lerpUnclamped(vec3f::zero().XYZ<double>(), vec3d::one() * 8.34, 6.78));
    std::cout << "" << std::endl;
    // logMat4(quatd::identity().toMat4());

    logVec2(vec2f(1.1f, 2.2f));

    std::cout << math::twoPi<double>() << std::endl;

    logVec2(vec2d::lerp(vec2f::zero().XY<double>(), vec2d::one() * 2.0, 0.5));


    logVec2(vec2f::lerpUnclamped(vec2f::zero(), vec2d::one().XY<float>(), 6.0));


    vec3f fvec = vec3d::one().ZYX<float>();

    logVec3(fvec.XYZ<float>());

    return 0;
}



// super cool namespace color : #E6DD9A