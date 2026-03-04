#include <iostream>


#include "Quaternions.hpp"
#include "Vectors.hpp"
#include "Matrices.hpp"



template<math::FloatingNumber F>
void logVec2(const vec2<F>& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ")" << std::endl;
}
template<math::FloatingNumber F>
void logVec3(const vec3<F>& vec)
{
    std::cout << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
}
template<math::FloatingNumber F>
void logQuat(const quat<F>& quat)
{
    std::cout << "(" << quat.w << ", " << quat.x << ", " << quat.y << ", " << quat.z << ")" << std::endl;
}
template<math::FloatingNumber F>
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
            if ( std::abs(value) > static_cast<F>(1e-10) ) std::cout << value << " ";
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
            if ( std::abs(value) > static_cast<F>(1e-10) ) std::cout << value << " ";
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
            if ( std::abs(value) > static_cast<F>(1e-10) ) std::cout << value << " ";
            else std::cout << "0" << " ";
        }

        std::cout << '\n';
    }
    std::cout << "" << std::endl;
}




int main() 
{
    quatd r(186.0, 8982.98576, 3.0, 5354.6789012456);
    quatd d(7657.5, 1.776, 435.5, 3.5); 
    dQuatd q(r, d);

    quatf fr(1.0f, 2.0f, 3.0f, 4.0f);
    quatf fd(0.5f, 1.5f, 2.5f, 3.5f); 
    dQuatf fq(fr, fd);

   
    std::cout << "Quaternion de float inverse (nombres simples) : " << '\n';
    logDualQuat(fq * fq.getInversedDualQuat());
    
    std::cout << std::endl;
    
    std::cout << "Quaternion de double inverse (avec nombres complexes) : " << '\n';
    logDualQuat(q * q.getInversedDualQuat());

    return 0;
}



// super cool namespace color : #E6DD9A