#include <cmath>
#include <concepts>

#include "Math\MathInternal.hpp"

#include <iostream>

namespace glMath
{
    
    #pragma region Constructors

    template<FloatingNumber F>
    inline mat3<F>::mat3(F m00, F m01, F m02, 
                         F m10, F m11, F m12,
                         F m20, F m21, F m22)
    {
        columns[0][0] = m00; columns[0][1] = m10; columns[0][2] = m20;
        columns[1][0] = m01; columns[1][1] = m11; columns[1][2] = m21;
        columns[2][0] = m02; columns[2][1] = m12; columns[2][2] = m22;
    }

    template<FloatingNumber F>
    inline mat3<F>::mat3()
    {
        F f0 = static_cast<F>(0.0);

        indices[0] = f0;
        indices[1] = f0;
        indices[2] = f0;
        indices[3] = f0;
        indices[4] = f0;
        indices[5] = f0;
        indices[6] = f0;
        indices[7] = f0;
        indices[8] = f0;
    }

    template<FloatingNumber F>
    inline mat3<F>::mat3(F scalar)
    {
        indices[0] = scalar;
        indices[1] = scalar;
        indices[2] = scalar;
        indices[3] = scalar;
        indices[4] = scalar;
        indices[5] = scalar;
        indices[6] = scalar;
        indices[7] = scalar;
        indices[8] = scalar;
    }

    #pragma endregion Constructors
    
    #pragma region StaticConstructors
    
    
    template<FloatingNumber F>
    inline mat3<F> mat3<F>::diagonal(F diagonal)
    {
        mat3<F> baseMat;

        baseMat.columns[0][0] = diagonal;
        baseMat.columns[1][1] = diagonal;
        baseMat.columns[2][2] = diagonal;

        return baseMat;
    }


    #pragma endregion StaticConstructors
    
    #pragma region Casting
    
    template<FloatingNumber F>
    template<FloatingNumber f>
    inline mat3<f> mat3<F>::as() const
    {
        std::numeric_limits<f> limit = std::numeric_limits<f>();
        f minLimit = limit.lowest();
        f maxLimit = limit.max();
        

        mat3<f> res;

        res.indices[0] = std::clamp(static_cast<f>(indices[0]), minLimit, maxLimit);
        res.indices[1] = std::clamp(static_cast<f>(indices[1]), minLimit, maxLimit);
        res.indices[2] = std::clamp(static_cast<f>(indices[2]), minLimit, maxLimit);
        res.indices[3] = std::clamp(static_cast<f>(indices[3]), minLimit, maxLimit);
        res.indices[4] = std::clamp(static_cast<f>(indices[4]), minLimit, maxLimit);
        res.indices[5] = std::clamp(static_cast<f>(indices[5]), minLimit, maxLimit);
        res.indices[6] = std::clamp(static_cast<f>(indices[6]), minLimit, maxLimit);
        res.indices[7] = std::clamp(static_cast<f>(indices[7]), minLimit, maxLimit);
        res.indices[8] = std::clamp(static_cast<f>(indices[8]), minLimit, maxLimit);

        return res;
    }


    template<FloatingNumber F>
    inline vec3<F> mat3<F>::rotatePoint(const mat3<F>& mat, const vec3<F>& point) 
    {
        return mat * point;
    }

    #pragma endregion Casting
    
    #pragma region MemberMethods

    template<FloatingNumber F>
    inline vec3<F> mat3<F>::rotatePoint(const vec3<F>& point) const
    {
        return *this * point;
    }

    
    template<FloatingNumber F>
    inline F mat3<F>::determinant() const
    {
        return columns[0][0] * (columns[1][1] * columns[2][2] - columns[2][1] * columns[1][2]) - 
               columns[1][0] * (columns[0][1] * columns[2][2] - columns[0][2] * columns[2][1]) + 
               columns[2][0] * (columns[0][1] * columns[1][2] - columns[1][1] * columns[0][2]);
    }

    template<FloatingNumber F>
    inline mat3<F>& mat3<F>::inverted()
    {
        F det = this->determinant();
    
        if (std::abs(det) > glMath::epsilon<F>()) 
        { 
            *this = this->getAdjugateMat() * (static_cast<F>(1.0) / det);  
        }

        return *this;
    }

    template<FloatingNumber F>
    inline mat3<F>& mat3<F>::transposed()
    {
        F m01 = columns[1][0];
        F m02 = columns[2][0];
        F m10 = columns[0][1];
        F m12 = columns[2][1];
        F m20 = columns[0][2];
        F m21 = columns[1][2];

        columns[0][1] = m01;
        columns[0][2] = m02;
        columns[1][0] = m10;
        columns[1][2] = m12;
        columns[2][0] = m20;
        columns[2][1] = m21;

        return *this;
    }

    template<FloatingNumber F>
    inline mat3<F> mat3<F>::getInvertedMat() const
    {
        mat3<F> res = *this;

        return res.inverted();
    }

    template<FloatingNumber F>
    inline mat3<F> mat3<F>::getTransposedMat() const
    {
        mat3<F> res = *this;

        return res.transposed();
    }

    template<FloatingNumber F>
    inline mat3<F> mat3<F>::getComatrix() const
    {
        mat3<F> res;

        res.columns[0][0] =  (columns[1][1] * columns[2][2] - columns[1][2] * columns[2][1]);
        res.columns[1][0] = -(columns[0][1] * columns[2][2] - columns[0][2] * columns[2][1]);
        res.columns[2][0] =  (columns[0][1] * columns[1][2] - columns[0][2] * columns[1][1]);

        res.columns[0][1] = -(columns[1][0] * columns[2][2] - columns[1][2] * columns[2][0]);
        res.columns[1][1] =  (columns[0][0] * columns[2][2] - columns[0][2] * columns[2][0]);
        res.columns[2][1] = -(columns[0][0] * columns[1][2] - columns[0][2] * columns[1][0]);

        res.columns[0][2] =  (columns[1][0] * columns[2][1] - columns[1][1] * columns[2][0]);
        res.columns[1][2] = -(columns[0][0] * columns[2][1] - columns[0][1] * columns[2][0]);
        res.columns[2][2] =  (columns[0][0] * columns[1][1] - columns[0][1] * columns[1][0]);

        return res;
    }

    template<FloatingNumber F>
    inline mat3<F> mat3<F>::getAdjugateMat() const 
    {
        mat3<F> res;

        res.columns[0][0] =  (columns[1][1] * columns[2][2] - columns[1][2] * columns[2][1]);
        res.columns[0][1] = -(columns[0][1] * columns[2][2] - columns[0][2] * columns[2][1]);
        res.columns[0][2] =  (columns[0][1] * columns[1][2] - columns[0][2] * columns[1][1]);

        res.columns[1][0] = -(columns[1][0] * columns[2][2] - columns[1][2] * columns[2][0]);
        res.columns[1][1] =  (columns[0][0] * columns[2][2] - columns[0][2] * columns[2][0]);
        res.columns[1][2] = -(columns[0][0] * columns[1][2] - columns[0][2] * columns[1][0]);

        res.columns[2][0] =  (columns[1][0] * columns[2][1] - columns[1][1] * columns[2][0]);
        res.columns[2][1] = -(columns[0][0] * columns[2][1] - columns[0][1] * columns[2][0]);
        res.columns[2][2] =  (columns[0][0] * columns[1][1] - columns[0][1] * columns[1][0]);

        return res;
    }

    template<FloatingNumber F>
    inline F& mat3<F>::at(int row, int col)
    {
        return columns[col][row];
    }

    template<FloatingNumber F>
    inline F mat3<F>::at(int row, int col) const
    {
        return columns[col][row];
    }

    // TODO:
    // ↓↓↓↓↓↓↓↓↓↓↓↓↓

    template<FloatingNumber F>
    inline mat2<F> mat3<F>::getSubmatrix(int row, int col) const
    {
        mat2<F> res;

        // Calculates the indices of the two rowValues we need to use, and store them in the array

        int rowIndices[2];

        for (int i = 0; i < 2; i++)
        {
            if (i < row)
            {
                rowIndices[i] = i;
            }
            else 
            {
                rowIndices[i] = i + 1;
            }
        }

        // Calculates the index of the column we need to use (twice)
        // and assign the value of the res matrix to the column, and the index stored inside the rowIndices (twice : 0 then 1)

        for (int i = 0; i < 2; i++)
        {
            int colToUse = 0;

            if (i < col)
            {
                colToUse = i;
            }
            else
            {
                colToUse = i + 1;
            }

            res.columns[i][0] = this->columns[colToUse][rowIndices[0]];
            res.columns[i][1] = this->columns[colToUse][rowIndices[1]];
        }

        return res;
    }

    template<FloatingNumber F>
    template<Number N>
    inline N mat3<F>::getMinor(int row, int col) const
    {
        mat2<F> mat = this->getSubmatrix(row, col);

        return mat.template determinant<N>();
    }

    template<FloatingNumber F>
    template<Number N>
    inline N mat3<F>::getCofactor(int row, int col) const
    {
        N minor = this->template getMinor<N>(row, col);

        return (row + col) % 2 == 0 ? minor * static_cast<N>(1.0) : minor * static_cast<N>(-1.0);
    }


    #pragma endregion MemberMethods
    
    #pragma region StaticMethods

    template<FloatingNumber F>
    inline F mat3<F>::determinant(const mat3<F>& mat)
    {
        return mat.determinant();
    }


    template<FloatingNumber F>
    inline mat3<F> mat3<F>::rotateX(F zAngDeg)
    {
        F ang = zAngDeg * glMath::degToRad<F>();
        F cosAng = static_cast<F>(std::cos(ang));
        F sinAng = static_cast<F>(std::sin(ang));

        mat3<F> res = mat3<F>::identity();


                                  res.columns[1][1] = cosAng; res.columns[2][1] = -sinAng;
                                  res.columns[1][2] = sinAng; res.columns[2][2] = cosAng;
    
        return res;
    }

    template<FloatingNumber F>
    inline mat3<F> mat3<F>::rotateY(F zAngDeg)
    {
        F ang = zAngDeg * glMath::degToRad<F>();
        F cosAng = static_cast<F>(std::cos(ang));
        F sinAng = static_cast<F>(std::sin(ang));

        mat3<F> res = mat3<F>::identity();

        res.columns[0][0] = cosAng;                            res.columns[2][0] = sinAng;

        res.columns[0][2] = -sinAng;                           res.columns[2][2] = cosAng;

        return res;
    }

    template<FloatingNumber F>
    inline mat3<F> mat3<F>::rotateZ(F zAngDeg)
    {
        F ang = zAngDeg * glMath::degToRad<F>();
        F cosAng = static_cast<F>(std::cos(ang));
        F sinAng = static_cast<F>(std::sin(ang));

        mat3<F> res = mat3<F>::identity();

        res.columns[0][0] = cosAng; res.columns[1][0] = -sinAng;
        res.columns[0][1] = sinAng; res.columns[1][1] = cosAng;

        return res;
    }

    
    template<FloatingNumber F>
    inline mat3<F> mat3<F>::fromQuat(const quat<F>& rotationQuat)
    {
        F xx = rotationQuat.x * rotationQuat.x;
        F yy = rotationQuat.y * rotationQuat.y;
        F zz = rotationQuat.z * rotationQuat.z;
        F ww = rotationQuat.w * rotationQuat.w;
        F xy = rotationQuat.x * rotationQuat.y;
        F xz = rotationQuat.x * rotationQuat.z;
        F wz = rotationQuat.w * rotationQuat.z;
        F wy = rotationQuat.w * rotationQuat.y;
        F wx = rotationQuat.w * rotationQuat.x;
        F yz = rotationQuat.y * rotationQuat.z;

        return mat3<F>(
            1 - 2 * (yy + zz), 2 * (xy - wz)    , 2 * (xz + wy),   
            2 * (xy + wz)    , 1 - 2 * (xx + zz), 2 * (yz - wx),    
            2 * (xz - wy)    , 2 * (yz + wx)    , 1 - 2 * (xx + yy)
        );
    }


    #pragma endregion 

    #pragma region ReferenceOperators

    template<FloatingNumber F>
    inline mat3<F>& mat3<F>::operator+(const mat3<F>& other)
    {
        return *this + other;
    }
    template<FloatingNumber F>
    inline mat3<F>& mat3<F>::operator+(F scalar)
    {
        return *this + scalar;
    }

    template<FloatingNumber F>
    inline mat3<F>& mat3<F>::operator-(const mat3<F>& other)
    {
        return *this - other;
    }
    template<FloatingNumber F>
    inline mat3<F>& mat3<F>::operator-(F scalar)
    {
        return *this - scalar;
    }

    template<FloatingNumber F>
    inline mat3<F>& mat3<F>::operator*(const mat3<F>& other)
    {
        return *this * other;
    }
    template<FloatingNumber F>
    inline mat3<F>& mat3<F>::operator*(F scalar)
    {
        return *this * scalar;
    }

    template<FloatingNumber F>
    inline mat3<F>& mat3<F>::operator/(F scalar)
    {
        return *this * scalar;
    }

    #pragma endregion 


    #pragma region ArithmeticOperators

    template<FloatingNumber F>
    inline mat3<F> operator+(const mat3<F>& a, const mat3<F>& b) 
    {
        mat3<F> res;

        res.indices[0] = a.indices[0] + b.indices[0];
        res.indices[1] = a.indices[1] + b.indices[1];
        res.indices[2] = a.indices[2] + b.indices[2];
        res.indices[3] = a.indices[3] + b.indices[3];
        res.indices[4] = a.indices[4] + b.indices[4];
        res.indices[5] = a.indices[5] + b.indices[5];
        res.indices[6] = a.indices[6] + b.indices[6];
        res.indices[7] = a.indices[7] + b.indices[7];
        res.indices[8] = a.indices[8] + b.indices[8];

        return res;
    }

    template<FloatingNumber F>
    inline mat3<F> operator-(const mat3<F>& a, const mat3<F>& b) 
    {
        mat3<F> res;

        res.indices[0] = a.indices[0] - b.indices[0];
        res.indices[1] = a.indices[1] - b.indices[1];
        res.indices[2] = a.indices[2] - b.indices[2];
        res.indices[3] = a.indices[3] - b.indices[3];
        res.indices[4] = a.indices[4] - b.indices[4];
        res.indices[5] = a.indices[5] - b.indices[5];
        res.indices[6] = a.indices[6] - b.indices[6];
        res.indices[7] = a.indices[7] - b.indices[7];
        res.indices[8] = a.indices[8] - b.indices[8];

        return res;
    }

    template<FloatingNumber F>
    inline mat3<F> operator*(const mat3<F>& a, const mat3<F>& b) 
    {
        mat3<F> res;

        res.columns[0][0] = a.columns[0][0] * b.columns[0][0] + a.columns[1][0] * b.columns[0][1] + a.columns[2][0] * b.columns[0][2];
        res.columns[1][0] = a.columns[0][0] * b.columns[1][0] + a.columns[1][0] * b.columns[1][1] + a.columns[2][0] * b.columns[1][2];
        res.columns[2][0] = a.columns[0][0] * b.columns[2][0] + a.columns[1][0] * b.columns[2][1] + a.columns[2][0] * b.columns[2][2];

        res.columns[0][1] = a.columns[0][1] * b.columns[0][0] + a.columns[1][1] * b.columns[0][1] + a.columns[2][1] * b.columns[0][2];
        res.columns[1][1] = a.columns[0][1] * b.columns[1][0] + a.columns[1][1] * b.columns[1][1] + a.columns[2][1] * b.columns[1][2];
        res.columns[2][1] = a.columns[0][1] * b.columns[2][0] + a.columns[1][1] * b.columns[2][1] + a.columns[2][1] * b.columns[2][2];

        res.columns[0][2] = a.columns[0][2] * b.columns[0][0] + a.columns[1][2] * b.columns[0][1] + a.columns[2][2] * b.columns[0][2];
        res.columns[1][2] = a.columns[0][2] * b.columns[1][0] + a.columns[1][2] * b.columns[1][1] + a.columns[2][2] * b.columns[1][2];
        res.columns[2][2] = a.columns[0][2] * b.columns[2][0] + a.columns[1][2] * b.columns[2][1] + a.columns[2][2] * b.columns[2][2];

        return res;
    }

    template<FloatingNumber F>
    inline mat3<F> operator*(const mat3<F>& mat, F scalar) 
    {
        mat3<F> res;

        res.indices[0] = mat.indices[0] * scalar;
        res.indices[1] = mat.indices[1] * scalar;
        res.indices[2] = mat.indices[2] * scalar;
        res.indices[3] = mat.indices[3] * scalar;
        res.indices[4] = mat.indices[4] * scalar;
        res.indices[5] = mat.indices[5] * scalar;
        res.indices[6] = mat.indices[6] * scalar;
        res.indices[7] = mat.indices[7] * scalar;
        res.indices[8] = mat.indices[8] * scalar;

        return res;
    }

    template<FloatingNumber F>
    inline mat3<F> operator*(F scalar, const mat3<F>& mat) 
    {
        mat3<F> res;

        res.indices[0] = mat.indices[0] * scalar;
        res.indices[1] = mat.indices[1] * scalar;
        res.indices[2] = mat.indices[2] * scalar;
        res.indices[3] = mat.indices[3] * scalar;
        res.indices[4] = mat.indices[4] * scalar;
        res.indices[5] = mat.indices[5] * scalar;
        res.indices[6] = mat.indices[6] * scalar;
        res.indices[7] = mat.indices[7] * scalar;
        res.indices[8] = mat.indices[8] * scalar;

        return res;
    }

    template<FloatingNumber F>
    inline vec3<F> operator*(const mat3<F>& mat, const vec3<F>& vec) 
    {
        return vec3<F>(
            mat.columns[0][0] * vec.x + mat.columns[1][0] * vec.y + mat.columns[2][0] * vec.z,
            mat.columns[0][1] * vec.x + mat.columns[1][1] * vec.y + mat.columns[2][1] * vec.z,
            mat.columns[0][2] * vec.x + mat.columns[1][2] * vec.y + mat.columns[2][2] * vec.z
        );
    }

    template<FloatingNumber F>
    inline mat3<F> operator/(const mat3<F>& mat, F scalar) 
    {
        if (scalar == static_cast<F>(0.0)) return mat;

        mat3<F> res;

        F invScalar = static_cast<F>(1.0) / scalar;

        res.indices[0] = mat.indices[0] * invScalar;
        res.indices[1] = mat.indices[1] * invScalar;
        res.indices[2] = mat.indices[2] * invScalar;
        res.indices[3] = mat.indices[3] * invScalar;
        res.indices[4] = mat.indices[4] * invScalar;
        res.indices[5] = mat.indices[5] * invScalar;
        res.indices[6] = mat.indices[6] * invScalar;
        res.indices[7] = mat.indices[7] * invScalar;
        res.indices[8] = mat.indices[8] * invScalar;

        return res;
    }



    template<FloatingNumber F>
    inline bool operator==(const mat3<F>& a, const mat3<F>& b) 
    {
        for (int i = 0; i < 9; i++)
        {
            if (std::abs(b.indices[i] - a.indices[i]) > glMath::epsilon<F>())
            {
                return false;
            } 
        }

        return true;
    }

    template<FloatingNumber F>
    inline bool operator!=(const mat3<F>& a, const mat3<F>& b)
    {
        return !(a == b);
    }

    #pragma endregion 
}
