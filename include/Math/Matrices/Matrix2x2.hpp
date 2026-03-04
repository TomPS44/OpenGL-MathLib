#pragma once

#include <concepts>

#include "Math\Concepts.hpp"

namespace math
{
    // A struct used to represent a Matrix2x2, with the values being stored in colum-major
    //
    // ( [0][0] [1][0] )
    // ( [0][1] [1][1] )
    // 
    //
    template<FloatingNumber F>
    struct mat2
    {
    public:
        union
        {
            F indices[4];   // [index] access
            F columns[2][2]; // [col][row] access
        };
        
    public: 
        // stored in column-major
        mat2(F m00, F m01, 
             F m10, F m11);

        mat2();

        template<FloatingNumber f>
        mat2<f> as() const;

        static mat2 rotateZ(F zAngDeg);

        template<Number N = F>
        N determinant() const;

        mat2& inverted();
        mat2& transposed();

        mat2 getInvertedMat() const;

        mat2 getTransposedMat() const;


        static mat2<F> diagonal(F diagonal);

        static mat2<F> identity();
        

        F& at(int row, int col);
        F at(int row, int col) const;        
    };

    template<FloatingNumber F>
    inline mat2<F> operator+(const mat2<F>& a, const mat2<F>& b);

    template<FloatingNumber F>
    inline mat2<F> operator-(const mat2<F>& a, const mat2<F>& b);

    template<FloatingNumber F>
    inline mat2<F> operator*(const mat2<F>& a, const mat2<F>& b);
    template<FloatingNumber F>
    inline mat2<F> operator*(const mat2<F>& a, F scalar);
    template<FloatingNumber F>
    inline mat2<F> operator*(F scalar, const mat2<F>& a);
    template<FloatingNumber F>
    inline vec2<F> operator*(const mat2<F>& a, const vec2<F>& vec);

    template<FloatingNumber F>
    inline mat2<F> operator/(const mat2<F>& a, F scalar);
}

#include "Math\Matrices\Matrix2x2.inl"