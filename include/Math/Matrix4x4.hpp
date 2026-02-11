#pragma once

#include <cmath>
#include <iostream>

#include "Math\MathInternal.hpp"

namespace math
{
    // A struct used to represent a Matrix4x4, with the values being stored in colum-major
    struct mat4
    {
    public:
        union
        {
            float indices[16];   // [index] access
            float columns[4][4]; // [col][row] access
        };
        
    public: 
        // stored in column-major
        mat4(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33)
        {
            columns[0][0] = m00; columns[0][1] = m10; columns[0][2] = m20; columns[0][3] = m30;
            columns[1][0] = m01; columns[1][1] = m11; columns[1][2] = m21; columns[1][3] = m31;
            columns[2][0] = m02; columns[2][1] = m12; columns[2][2] = m22; columns[2][3] = m32;
            columns[3][0] = m03; columns[3][1] = m13; columns[3][2] = m23; columns[3][3] = m33;
        }

        mat4()
        {
            for (int i = 0; i < 16; i++)
            {
                indices[i] = 0.0f;
            }
        }

        static mat4 identity()
        {
            return mat4(1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f);
        }
        static mat4 zero() 
        {
            return mat4(0.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 0.0f);
        }

        float& at(int row, int col) 
        {
            return indices[col * 4 + row];
        }
        float at(int row, int col) const
        {
            return indices[col * 4 + row];
        }

        // friend mat4 operator*(const mat4& a, const mat4& b);
        
    };

    inline mat4 operator*(const mat4& a, const mat4& b)
    {
        mat4 result;

        for (int col = 0; col < 4; col++)
        {
            for (int row = 0; row < 4; row++)
            {
                result.columns[col][row] = 
                    a.columns[0][row] * b.columns[col][0] +
                    a.columns[1][row] * b.columns[col][1] +
                    a.columns[2][row] * b.columns[col][2] +
                    a.columns[3][row] * b.columns[col][3];
            }
        }

        return result;
    }

    inline bool operator==(const mat4& a, const mat4& b)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (std::abs(a.columns[j][i] - b.columns[j][i]) > math::epsilon<float>()) { return false; }
            }
        }

        return true;
    }
}