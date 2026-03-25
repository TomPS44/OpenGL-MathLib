#pragma once

#include <concepts>

#include "Math\Concepts.hpp"

namespace glMath
{   
    /// @brief A struct used to represent a Matrix2x2
    /// @tparam F The type of the values stored in the 2x2 Matrix, a FloatingNumber, so a float or a double
    template<FloatingNumber F>
    struct alignas(sizeof(F) * 4) mat2
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

        mat2(F scalar);

        mat2();

        template<FloatingNumber f>
        mat2<f> as() const;

        static mat2 rotateZ(F zAngDeg);

        vec2<F> rotatePoint(const vec2<F>& point) const;
        static vec2<F> rotatePoint(const mat2& mat, const vec2<F>& vec);

        F determinant() const;
        static F determinant(const mat2<F>& mat);

        mat2& inverse();
        mat2& transpose();

        mat2 getInvertedMat() const;

        mat2 getTransposedMat() const;

        static mat2 inverted(const mat2& mat);
        static mat2 transposed(const mat2& mat);


        static mat2<F> diagonal(F diagonal);


        inline static mat2 identity() { return mat2(1.0, 0.0,
                                                    0.0, 1.0); };        

        F& at(int row, int col);
        F at(int row, int col) const; 
        
        
        mat2& operator+=(const mat2& other);
        mat2& operator+=(F scalar);

        mat2& operator-=(const mat2& other);
        mat2& operator-=(F scalar);

        mat2& operator*=(const mat2& other);
        mat2& operator*=(F scalar);

        mat2& operator/=(F scalar);
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


    template<FloatingNumber F>
    inline bool operator==(const mat2<F>& a, const mat2<F>& b);
    template<FloatingNumber F>
    inline bool operator!=(const mat2<F>& a, const mat2<F>& b);
}

#include "Math\Matrices\Matrix2x2.inl"