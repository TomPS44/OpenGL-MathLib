#include <iostream>
#include "Math.hpp"

void logVec2(const vec2& vec)
{
    std::cout << "(" << vec.x() << ", " << vec.y() << ")" << std::endl;
}
void logVec3(const vec3& vec)
{
    std::cout << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")" << std::endl;
}
void logQuat(const quat& quat)
{
    std::cout << "(" << quat.w() << ", " << quat.x() << ", " << quat.y() << ", " << quat.z() << ")" << std::endl;
}
void logMat4(const mat4& mat)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << mat.at(i, j) << " ";
        }
        std::cout << '\n';
    }
}


int main() 
{
    mat4 T = mat4::identity();
    T.at(0, 3) = 10.0f;

    mat4 S = mat4::identity();
    S.at(0, 0) = 2.0f; S.at(1, 1) = 2.0f; S.at(2, 2) = 2.0f;

    mat4 combined = T * S;

    std::cout << Mathf::nearlyEqual(combined.at(0, 3), T.at(0, 3)) << std::endl;
    logMat4(combined);
    
    return 0;
}



// super cool namespace color : #E6DD9A