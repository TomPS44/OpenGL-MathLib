#include <iostream>
#include <concepts>

// #include "Math.hpp"
#include "Vectors.hpp"
#include "Matrices.hpp"
#include "Quaternions.hpp"

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
template<std::floating_point F>
void logDualQuat(const dualQuat<F>& dQuat)
{
    std::cout << "(" << dQuat.real.w << ", " << dQuat.real.x << ", " << dQuat.real.y << ", " << dQuat.real.z << " | " << 
                 dQuat.dual.w << ", " << dQuat.dual.x << ", " << dQuat.dual.y << ", " << dQuat.dual.z << ")" << std::endl;
}
template<std::floating_point F>
void logMat4(const mat4<F>& mat)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            F value = mat.columns[j][i];
            if ( std::abs(value) > static_cast<F>(1e-10) ) std::cout << value << " ";
            else std::cout << "0" << " ";
        }

        std::cout << '\n';
    }
}
template<std::floating_point F>
void logMat3(const mat3<F>& mat)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            F value = mat.columns[j][i];
            if ( std::abs(value) > static_cast<F>(1e-10) ) std::cout << value << " ";
            else std::cout << "0" << " ";
        }

        std::cout << '\n';
    }
}
template<std::floating_point F>
void logMat2(const mat2<F>& mat)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            F value = mat.columns[j][i];
            if ( std::abs(value) > static_cast<F>(1e-10) ) std::cout << value << " ";
            else std::cout << "0" << " ";
        }

        std::cout << '\n';
    }
    std::cout << "" << std::endl;
}


int main() 
{
    // quatf rotation = quatf::identity();
    // vec3f translation = (vec3f::up() + vec3f::left()) * 2.0f;

    // logQuat(0.5f * (quatf::getPureQuat(translation) * rotation));

    dualQuatd dQuat = { quatd::fromEuler(15.0f, 30.0f, 45.0f), vec3d(0.333f, 0.5f, 1.0f) };
    dQuatf fDQuat = dQuat.as<float>();

    logDualQuat(dQuat);
    logVec3(fDQuat.getTranslation());
    std::cout << typeid(dQuat.real.w).name() << std::endl;
    std::cout << typeid(fDQuat.real.w).name() << std::endl;

    vec3f target = { 1.0f, 3.0f, 0.0f };
    dualQuatf move = { quatf::fromEuler(0.0f, 0.0f, -90.0f), vec3f(0.0f, 2.0f, -3.0f) };

    logVec3(move.transformPoint(target));

    return 0;
}



// super cool namespace color : #E6DD9A