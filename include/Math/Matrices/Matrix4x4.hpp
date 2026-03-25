#pragma once

#include <concepts>

#include "Math\Concepts.hpp"

namespace glMath
{
    template<FloatingNumber F>
    struct vec3;

    template<FloatingNumber F>
    struct vec4;

    template<FloatingNumber F>
    struct quat;

    template<FloatingNumber F>
    struct mat3;

    template<FloatingNumber F>
    struct dualQuat;

    /// @brief A struct used to represent a 4x4 Matrix
    /// @tparam F The type of the values stored in the 4x4 Matrix, a FloatingNumber, so a float or a double
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

        /// @brief A function to convert the 4x4 matrix to a 3x3 matrix.
        /// @return A 3x3 matrix extracted from the top-left corner of the 4x4 matrix.
        mat3<F> toMat3() const;


        static mat4 diagonal(F diagonal);


        inline static mat4 identity() { return mat4(1.0, 0.0, 0.0, 0.0,
                                                    0.0, 1.0, 0.0, 0.0,
                                                    0.0, 0.0, 1.0, 0.0,
                                                    0.0, 0.0, 0.0, 1.0); };

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

        /// @brief A function to generates a lookAt matrix
        /// @param eye The position of the element looking
        /// @param target The position of the element to look at
        /// @param worldUp The world up vector
        /// @return Returns a new 4X4 matrix of the same type 
        static mat4 lookAt(const vec3<F>& eye, const vec3<F>& target, const vec3<F>& worldUp);

        /// @brief A function to generate a perspective matrix
        /// @param fovInRad The Field Of View of the camera, IN RADIANS
        /// @param aspectRatio The aspect ratio of the window
        /// @param near The near clipping plane
        /// @param far The far clipping plane
        /// @return Return a new 4X4 matrix of the same type
        static mat4 perspective(F fovInRad, F aspectRatio, F near, F far);

        /// @brief A function to generate an orthographic matrix
        /// @param left The left clipping plpane
        /// @param right The right clipping plane
        /// @param bottom The top clipping plane
        /// @param top The bottom clipping plane
        /// @param near The near clipping plane
        /// @param far The far clipping plane
        /// @return Return a new 4X4 matrix of the same type
        static mat4 orthographic(F left, F right, F bottom, F top, F near, F far);

        
        vec4<F> transformPoint(const vec4<F>& point) const;
        static vec4<F> transformPoint(const mat4& mat, const vec4<F>& point);


        /// @brief A function to transpose a matrix, inversing its rows and its columns
        /// @return Returns a reference to the matrix, but transposed
        mat4& transpose();
        /// @brief A function to transpose a matrix, inversing its rows and columns
        /// @return Returns a new 4x4 matrix of the same type, but transposed
        mat4 getTransposedMat() const;
        static mat4 transpose(const mat4& mat);

        /// @brief A function to inverse a matrix
        /// @return Returns a reference to the matrix, but inversed. 
        /// If its determinant is or is practically zero, returns a new matrix, identic as the original 
        mat4& inverse();
        /// @brief A function to transpose a matrix, inversing its rows and columns
        /// @return Returns a new 4x4 matrix of the same type, but transposed
        mat4 getInversedMat() const;
        static mat4 inverse(const mat4& mat);


        /// @brief A function to get the matrix of cofactors
        /// @return Returns a new matrix of the same type, but made of its cofactors 
        mat4 getComatrix() const;
        /// @brief A function to get the matrix of cofactors
        /// @param mat The matrix which will be used to calculate all the cofactors
        /// @return Returns a new 4x4 matrix of the same type, but made of the cofactors of the specified matrix
        static mat4 getComatrix(const mat4<F>& mat);

        /// @brief A function to get the adjugate of a matrix, the cofactor matrix transposed 
        /// @return Returns a new 4x4 matrix, of the same type but that is the adjugate of itself
        mat4 getAdjugate() const;
        /// @brief A function to get the adjufate of a matrix, the cofactor matrix transposed
        /// @param mat The matrix which will be used to calculate the adjugate
        /// @return Returns a new 4x4 matrix of the same type, but that is the adjugate of the specified matrix
        static mat4 getAdjugate(const mat4<F>& mat);

        /// @brief A function to get the normal of a matrix, the top-left 3x3 matrix inversed and then transposed
        /// @return Returns a new 3x3 matrix of the same type, but that is the normal of itself
        mat3<F> getNormalMat() const;
        /// @brief A function to get the normal of a matrix, the top-left 3x3 matrix inversed and then transposed
        /// @param mat The matrix which will be used to calculate the normal
        /// @return Returns a new 3x3 matrix of the same type, but that is the normal of the specified matrix 
        static mat3<F> getNormalMat(const mat4<F>& mat);


        /// @brief A function to get a smaller matrix from a bigger one
        /// @param row The row (0-3) to remove
        /// @param col The column (0-3) to remove
        /// @return Return a new 3x3 matrix of the same type
        mat3<F> getSubmatrix(int row, int col) const;

        /// @brief A function to get the minor of a smaller matrix from a bigger one
        /// @param row The row (0-3) to remove
        /// @param col The column (0-3) to remove
        /// @return Return the determinant of the 3x3 matrix, as the type of the original matrix 
        F getMinor(int row, int col) const;
        /// @brief A function to get the cofactor of a smaller matrix from a bigger one
        /// @param row The row (0-3) to remove
        /// @param col The column (0-3) to remove
        /// @return Return the cofactor of the 3x3 matrix, as the type of the original matrix
        F getCofactor(int row, int col) const;

        /// @brief A function to get the determinant of a matrix
        /// @return Return the determinant of the matrix that called the object, as the type of the matrix
        F determinant() const;
        /// @brief A function to get the determinant of a matrix
        /// @param mat The matrix which will be used to calculate the determinant
        /// @return Return the determinant of the specified matrix, as the type of the matrix
        static F determinant(const mat4<F>& mat);
        
        /// @brief A function to access the value at a certain position
        /// @param row The row (0-3) of the value. If the value is less than 0, or greater than 3, it doesn't cause an error
        /// @param col The column (0-3) of the value. If the value is less than 0, or greater than 3, it doesn't cause an error
        /// @return Returns a reference to the value at the specified position, allowing it to be changed 
        F& at(int row, int col);
        /// @brief A function to read the value at a certain position (ReadOnly)
        /// @param row The row (0-3) of the value. If the value is less than 0, or greater than 3, it doesn't cause an error
        /// @param col The column (0-3) of the value. If the value is less than 0, or greater than 3, it doesn't cause an error
        /// @return Returns a const copy to the value at the specified position, allowing it to be read but not changed 
        const F at(int row, int col) const;   
        
        
        mat4& operator+=(const mat4& other);
        mat4& operator+=(F scalar);

        mat4& operator-=(const mat4& other);
        mat4& operator-=(F scalar);
        
        mat4& operator*=(const mat4& other);
        mat4& operator*=(F scalar);
    
        mat4& operator/=(F scalar);
    };

    template<FloatingNumber F>
    inline mat4<F> operator*(const mat4<F>& a, const mat4<F>& b);

    template<FloatingNumber F>
    inline vec4<F> operator*(const mat4<F>& mat, const vec4<F>& vec);

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


    template<FloatingNumber F>
    inline bool operator==(const mat4<F>& a, const mat4<F>& b);

    template<FloatingNumber F>
    inline bool operator!=(const mat4<F>& a, const mat4<F>& b);
}

#include "Math\Matrices\Matrix4x4.inl"