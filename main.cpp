#include <iostream>
#include <concepts>
#include <iomanip>
#include <cmath>
#include <string>

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


void printTest(const std::string& testName, bool success)
{
    std::cout << "[ ";

    if (success) 
    {
        // Code ANSI pour le vert
        std::cout << "\033[32mPASS\033[0m";
    } 
    else 
    {
        // Code ANSI pour le rouge
        std::cout << "\033[31mFAIL\033[0m";
    }

    std::cout << " ] " << testName << std::endl;
}

int main() 
{
    // Paramètres de la simulation
    vec3f cameraPos(0, 0, 0);
    vec3f targetStart(0, 0, 1);  // Regarde devant (Z)
    vec3f targetEnd(1, 0, 0);    // Regarde à droite (X)
    vec3f worldUp(0, 1, 0);
    
    // 1. Calcul des quaternions cibles
    quatf qStart = quatf::lookAt(cameraPos, targetStart, worldUp);
    quatf qEnd   = quatf::lookAt(cameraPos, targetEnd, worldUp);
    
    // 2. Interpolation à 25% du chemin
    float t = 0.25f;
    quatf qCurrent = quatf::slerp(qStart, qEnd, t);
    
    // 3. Validation mathématique
    // À 25% entre 0° et 90°, on doit être à exactement 22.5° sur l'axe Y.
    // Le W d'un quaternion est cos(angle/2), donc cos(11.25°)
    float expectedW = std::cos(11.25f * (3.14159265f / 180.0f));
    
    printTest("Smooth Camera Slerp (25%)", nearlyEqual(qCurrent.w, expectedW));


    return 0;
}



// super cool namespace color : #E6DD9A