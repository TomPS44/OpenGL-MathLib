#pragma once

#include <concepts>

#include "Math\Concepts.hpp"

namespace math
{
     
    template<FloatingNumber F>
    struct quat;

    template<FloatingNumber F>
    struct mat2;

    // A struct used to represent a 3x3 Matrix, with the values being stored in colum-major : 
    //
    // ( [0][0] [1][0] [2][0] )
    // ( [0][1] [1][1] [2][1] )
    // ( [0][2] [1][2] [2][2] )
    //
    template<FloatingNumber F>
    struct mat3
    {
    public:
        union
        {
            F columns[3][3]; // [col][row] access
            F indices[9];   // [index] access
        };
        
    public: 
        // stored in column-major
        mat3(F m00, F m01, F m02,
             F m10, F m11, F m12,
             F m20, F m21, F m22);

        mat3();

        mat3(F scalar);

        template<FloatingNumber f>
        mat3<f> as() const;

        static mat3 rotateX(F xAngDeg);
        static mat3 rotateY(F yAngDeg);
        static mat3 rotateZ(F zAngDeg);

        /// @brief A method to generate a mat3 from a quaternion
        /// @param rotationQuat The quaternion that contains the wanted rotation
        /// @return A mat3 coming from the rotationQuat quaternion
        static mat3 fromQuat(const quat<F>& rotationQuat);

        
        

        template<Number N = F>
        N determinant() const;

        mat3& inverted();
        mat3& transposed();

        mat3 getInvertedMat() const;

        mat3 getTransposedMat() const;

        mat3 getComatrix() const;

        mat3 getAdjugateMat() const;

        static mat3<F> diagonal(F diagonal);

        static mat3<F> identity();
        

        F& at(int row, int col);
        F at(int row, int col) const;  
        

        template<Number N = F>
        N getMinor(int row, int col) const;

        template<Number N = F>
        N getCofactor(int row, int col) const;

        mat2<F> getSubmatrix(int row, int col) const;
    };

    template<FloatingNumber F>
    inline mat3<F> operator+(const mat3<F>& a, const mat3<F>& b);

    template<FloatingNumber F>
    inline mat3<F> operator-(const mat3<F>& a, const mat3<F>& b);

    template<FloatingNumber F>
    inline mat3<F> operator*(const mat3<F>& a, const mat3<F>& b);
    template<FloatingNumber F>
    inline mat3<F> operator*(const mat3<F>& a, F scalar);
    template<FloatingNumber F>
    inline mat3<F> operator*(F scalar, const mat3<F>& a);
    template<FloatingNumber F>
    inline vec3<F> operator*(const mat3<F>& a, const vec3<F>& vec);

    template<FloatingNumber F>
    inline mat3<F> operator/(const mat3<F>& a, F scalar);
}

#include "Math\Matrices\Matrix3x3.inl"