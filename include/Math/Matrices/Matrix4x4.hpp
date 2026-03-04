#pragma once

#include <concepts>

#include "Math\Concepts.hpp"

namespace math
{
    template<FloatingNumber F>
    struct vec3;

    template<FloatingNumber F>
    struct quat;

    template<FloatingNumber F>
    struct mat3;

    template<FloatingNumber F>
    struct dualQuat;

    // A struct used to represent a Matrix4x4, with the values being stored in colum-major
    //
    // ( [0][0] [1][0] [2][0] [3][0] )
    // ( [0][1] [1][1] [2][1] [3][1] )
    // ( [0][2] [1][2] [2][2] [3][2] )
    // ( [0][3] [1][3] [2][3] [3][3] )
    //
    template<FloatingNumber F>
    struct alignas(sizeof(F) * 4) mat4
    {
    public:
        union
        {
            F indices[16];   // [index] access
            F columns[4][4]; // [col][row] access
        };
        
    public: 
        mat4(F m00, F m01, F m02, F m03,
             F m10, F m11, F m12, F m13,
             F m20, F m21, F m22, F m23,
             F m30, F m31, F m32, F m33);
        mat4();
        mat4(F scalar);


        template<FloatingNumber f>
        mat4<f> as() const;

        mat3<F> toMat3() const;


        static mat4 diagonal(F diagonal);

        static mat4 identity();

        static mat4 translate(const vec3<F>& translation);
        static mat4 translate(F tx, F ty, F tz);

        static mat4 scale(const vec3<F>& scale);
        static mat4 scale(F sx, F sy, F sz);

        static mat4 rotateX(F xAngDegrees);
        static mat4 rotateY(F yAngDegrees);
        static mat4 rotateZ(F zAngDegrees);

        static mat4 fromQuat(const quat<F>& rotationQuat);
        static mat4 fromDualQuat(const dualQuat<F>& dQuat);

        static mat4 fromMat3(const mat3<F>& mat);

        static mat4 lookAt(const vec3<F>& eye, const vec3<F>& target, const vec3<F>& up);

        template<Number N>
        static N determinant(const mat4<F>& mat);

        
        mat4& transposed();
        mat4 getTransposedMat() const;

        mat4& inversed();
        mat4 getInversedMat() const;

        mat4 getComatrix() const;

        mat4 getAdjugate() const;


        mat3<F> getNormalMat() const;


        mat3<F> getSubmatrix(int row, int col) const;

        template<Number N = F>
        N getMinor(int row, int col) const;

        template<Number N = F>
        N getCofactor(int row, int col) const;


        template<Number N = F>
        N determinant() const;
        

        F& at(int row, int col);
        F at(int row, int col) const;        
    };

    template<FloatingNumber F>
    inline mat4<F> operator*(const mat4<F>& a, const mat4<F>& b);

    template<FloatingNumber F>
    inline mat4<F> operator+(const mat4<F>& a, const mat4<F>& b);

    template<FloatingNumber F>
    inline mat4<F> operator-(const mat4<F>& a, const mat4<F>& b);

    template<FloatingNumber F>
    inline mat4<F> operator*(const mat4<F>& mat, F scalar);

    template<FloatingNumber F>
    inline mat4<F> operator*(F scalar, const mat4<F>& mat);

    template<FloatingNumber F>
    inline mat4<F> operator/(const mat4<F>& mat, F scalar);
}

#include "Math\Matrices\Matrix4x4.inl"