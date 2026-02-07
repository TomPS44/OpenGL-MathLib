#pragma once

#include <cmath>
#include <iostream>

#include "Math\MathInternal.hpp"

namespace Mathematics
{
    // A struct used to represent a Matrix4x4, with the values being stored in colum-major
    struct mat4
    {
    public:
        union
        {
            float m_Indices[16];   // [index] access
            float m_Columns[4][4]; // [col][row] access
        };
        
    public: 
        // stored in column-major
        mat4(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33)
        {
            m_Columns[0][0] = m00; m_Columns[0][1] = m10; m_Columns[0][2] = m20; m_Columns[0][3] = m30;
            m_Columns[1][0] = m01; m_Columns[1][1] = m11; m_Columns[1][2] = m21; m_Columns[1][3] = m31;
            m_Columns[2][0] = m02; m_Columns[2][1] = m12; m_Columns[2][2] = m22; m_Columns[2][3] = m32;
            m_Columns[3][0] = m03; m_Columns[3][1] = m13; m_Columns[3][2] = m23; m_Columns[3][3] = m33;
        }

        mat4()
        {
            for (int i = 0; i < 16; i++)
            {
                m_Indices[i] = 0.0f;
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
            return m_Indices[col * 4 + row];
        }
        float at(int row, int col) const
        {
            return m_Indices[col * 4 + row];
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
                result.m_Columns[col][row] = 
                    a.m_Columns[0][row] * b.m_Columns[col][0] +
                    a.m_Columns[1][row] * b.m_Columns[col][1] +
                    a.m_Columns[2][row] * b.m_Columns[col][2] +
                    a.m_Columns[3][row] * b.m_Columns[col][3];
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
                if (std::abs(a.at(i, j) - b.at(i, j)) > Constants::Epsilon) { return false; }
            }
        }

        return true;
    }
    
    
}