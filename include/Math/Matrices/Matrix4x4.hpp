#pragma once

#include <concepts>


namespace math
{
    

    // A struct used to represent a Matrix4x4, with the values being stored in colum-major
    //
    // ( [0][0] [1][0] [2][0] [3][0] )
    // ( [0][1] [1][1] [2][1] [3][1] )
    // ( [0][2] [1][2] [2][2] [3][2] )
    // ( [0][3] [1][3] [2][3] [3][3] )
    //
    template<std::floating_point F>
    struct alignas(16) mat4
    {
    public:
        union
        {
            F indices[16];   // [index] access
            F columns[4][4]; // [col][row] access
        };
        
    public: 
        // stored in column-major
        mat4(F m00, F m01, F m02, F m03,
             F m10, F m11, F m12, F m13,
             F m20, F m21, F m22, F m23,
             F m30, F m31, F m32, F m33);

        mat4();

        template<std::floating_point f>
        mat4<f> as() const;

        static mat4 diagonal(F diagonal);

        static mat4 identity();
        

        F& at(int row, int col);
        F at(int row, int col) const;        
    };

    template<std::floating_point F>
    inline mat4<F> operator*(const mat4<F>& a, const mat4<F>& b);

    

}

#include "Math\Matrices\Matrix4x4.inl"