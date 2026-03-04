#include <cmath>
#include <concepts>

#include "Math\MathInternal.hpp"

namespace math
{
    #pragma region Constructors

    template<FloatingNumber F>
    inline mat4<F>::mat4(F m00, F m01, F m02, F m03,
                         F m10, F m11, F m12, F m13,
                         F m20, F m21, F m22, F m23,
                         F m30, F m31, F m32, F m33)
    {
        columns[0][0] = m00; columns[0][1] = m10; columns[0][2] = m20; columns[0][3] = m30;
        columns[1][0] = m01; columns[1][1] = m11; columns[1][2] = m21; columns[1][3] = m31;
        columns[2][0] = m02; columns[2][1] = m12; columns[2][2] = m22; columns[2][3] = m32;
        columns[3][0] = m03; columns[3][1] = m13; columns[3][2] = m23; columns[3][3] = m33;
    }

    template<FloatingNumber F>
    inline mat4<F>::mat4()
    {
        F f0 = static_cast<F>(0.0);

        for (int i = 0; i < 16; i++)
        {
            indices[i] = f0;
        }
    }

    template<FloatingNumber F>
    inline mat4<F>::mat4(F scalar)
    {
        for (int i = 0; i < 16; i++)
        {
            indices[i] = scalar;
        }
    }

    #pragma endregion

    #pragma region Casting

    template<FloatingNumber F>
    template<FloatingNumber f>
    inline mat4<f> mat4<F>::as() const
    {
        mat4<f> res;

        for (int i = 0; i < 16; i++)
        {
            res.indices[i] = static_cast<f>(indices[i]);
        }

        return res;
    }

    #pragma endregion

    #pragma region StaticMethods

    template<FloatingNumber F>
    inline mat4<F> mat4<F>::diagonal(F diagonal)
    {
        mat4<F> baseMat;

        baseMat.columns[0][0] = diagonal;
        baseMat.columns[1][1] = diagonal;
        baseMat.columns[2][2] = diagonal;
        baseMat.columns[3][3] = diagonal;

        return baseMat;
    }

    template<FloatingNumber F>
    inline mat4<F> mat4<F>::identity()
    {
        mat4<F> baseMat;

        F f1 = static_cast<F>(1.0);

        baseMat.columns[0][0] = f1;
        baseMat.columns[1][1] = f1;
        baseMat.columns[2][2] = f1;
        baseMat.columns[3][3] = f1;

        return baseMat;
    }


    template<FloatingNumber F>
    inline mat4<F> mat4<F>::translate(const vec3<F>& translation)
    {
        return mat4<F>::translate(translation.x, translation.y, translation.z);
    }

    template<FloatingNumber F>
    inline mat4<F> mat4<F>::translate(F tx, F ty, F tz)
    {
        mat4<F> res = mat4<F>::identity();

        res.columns[3][0] = tx;
        res.columns[3][1] = ty;
        res.columns[3][2] = tz;

        return res;
    }


    template<FloatingNumber F>
    inline mat4<F> mat4<F>::scale(const vec3<F>& scale)
    {
        return mat4<F>::scale(scale.x, scale.y, scale.z);
    }

    template<FloatingNumber F>
    inline mat4<F> mat4<F>::scale(F sx, F sy, F sz)
    {
        mat4<F> res = mat4<F>::identity();

        res.columns[0][0] = sx;
        res.columns[1][1] = sy;
        res.columns[2][2] = sz;

        return res;
    }


    template<FloatingNumber F>
    inline mat4<F> mat4<F>::rotateX(F xAngDeg) 
    {
        F ang = xAngDeg * math::degToRad<F>();
        F cx = static_cast<F>(std::cos(ang));
        F sx = static_cast<F>(std::sin(ang));

        mat4<F> res = mat4<F>::identity;

        res.columns[1][1] = cx;
        res.columns[2][1] = -sx;
        res.columns[1][2] = sx;
        res.columns[2][2] = cx;
    }

    template<FloatingNumber F>
    inline mat4<F> mat4<F>::rotateY(F xAngDeg) 
    {
        F ang = xAngDeg * math::degToRad<F>();
        F cx = static_cast<F>(std::cos(ang));
        F sx = static_cast<F>(std::sin(ang));

        mat4<F> res = mat4<F>::identity;

        res.columns[0][0] = cx;
        res.columns[2][0] = sx;
        res.columns[0][2] = -sx;
        res.columns[2][2] = cx;
    }

    template<FloatingNumber F>
    inline mat4<F> mat4<F>::rotateZ(F xAngDeg) 
    {
        F ang = xAngDeg * math::degToRad<F>();
        F cx = static_cast<F>(std::cos(ang));
        F sx = static_cast<F>(std::sin(ang));

        mat4<F> res = mat4<F>::identity;

        res.columns[0][0] = cx;
        res.columns[1][0] = -sx;
        res.columns[0][1] = sx;
        res.columns[1][1] = cx;
    }

    template<FloatingNumber F>
    inline mat4<F> mat4<F>::fromQuat(const quat<F>& rotationQuat)
    {
        F xx = rotationQuat.x * rotationQuat.x;
        F yy = rotationQuat.y * rotationQuat.y;
        F zz = rotationQuat.z * rotationQuat.z;
        F xy = rotationQuat.x * rotationQuat.y;
        F wz = rotationQuat.w * rotationQuat.z;
        F wy = rotationQuat.w * rotationQuat.y;
        F wx = rotationQuat.w * rotationQuat.x;
        F xz = rotationQuat.x * rotationQuat.z;
        F yz = rotationQuat.y * rotationQuat.z;

        F f0 = static_cast<F>(0.0);

        return mat4<F>(1 - 2 * (yy + zz), 2 * (xy - wz)    , 2 * (xz + wy)    , f0,
                       2 * (xy + wz)    , 1 - 2 * (xx + zz), 2 * (yz - wx)    , f0,
                       2 * (xz - wy)    , 2 * (yz + wx)    , 1 - 2 * (xx + yy), f0,
                       f0               , f0               , f0               , static_cast<F>(1.0));
    }

    template<FloatingNumber F>
    inline mat4<F> mat4<F>::fromDualQuat(const dualQuat<F>& dQuat)
    {
        quat<F> real = dQuat.real;

        F xx = real.x * real.x;
        F yy = real.y * real.y;
        F zz = real.z * real.z;
        F xy = real.x * real.y;
        F wz = real.w * real.z;
        F wy = real.w * real.y;
        F wx = real.w * real.x;
        F xz = real.x * real.z;
        F yz = real.y * real.z;

        F f0 = static_cast<F>(0.0);

        vec3<F> t = dQuat.getTranslation();

        return mat4<F>(1 - 2 * (yy + zz), 2 * (xy - wz)    , 2 * (xz + wy)    , t.x,
                       2 * (xy + wz)    , 1 - 2 * (xx + zz), 2 * (yz - wx)    , t.y,
                       2 * (xz - wy)    , 2 * (yz + wx)    , 1 - 2 * (xx + yy), t.z,
                       f0               , f0               , f0               , static_cast<F>(1.0));
    }


    template<FloatingNumber F>
    inline mat4<F> mat4<F>::fromMat3(const mat3<F>& mat)
    {
        mat4<F> res = mat4<F>::identity();

        res.columns[0][0] = mat.columns[0][0];
        res.columns[0][1] = mat.columns[0][1];
        res.columns[0][2] = mat.columns[0][2];
        res.columns[1][0] = mat.columns[1][0];
        res.columns[1][1] = mat.columns[1][1];
        res.columns[1][2] = mat.columns[1][2];
        res.columns[2][0] = mat.columns[2][0];
        res.columns[2][1] = mat.columns[2][1];
        res.columns[2][2] = mat.columns[2][2];

        return res;
    }

    #pragma endregion

    #pragma region MemberMethods

    template<FloatingNumber F>
    inline F& mat4<F>::at(int row, int col)
    {
        return columns[col][row];
    }
    template<FloatingNumber F>
    inline F mat4<F>::at(int row, int col) const
    {
        return columns[col][row];
    }


    template<FloatingNumber F>
    inline mat3<F> mat4<F>::getSubmatrix(int row, int col) const
    {
        mat3<F> res;

        // Calculates the indices of the two rowValues we need to use, and store them in the array

        int rowIndices[3];

        for (int i = 0; i < 3; i++)
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

        for (int i = 0; i < 3; i++)
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
            res.columns[i][2] = this->columns[colToUse][rowIndices[2]];
        }

        return res;
    }

    template<FloatingNumber F>
    template<Number N>
    inline N mat4<F>::getMinor(int row, int col) const
    {
        mat3<F> mat = this->getSubmatrix(row, col);

        return mat.template determinant<N>();
    }

    template<FloatingNumber F>
    template<Number N>
    inline N mat4<F>::getCofactor(int row, int col) const
    {
        N minor = this->template getMinor<N>(row, col);

        return (row + col) % 2 == 0 ? minor * static_cast<N>(1.0) : minor * static_cast<N>(-1.0);
    }

    #pragma endregion

    #pragma region Constructors

    template<FloatingNumber F>
    inline mat4<F> operator*(const mat4<F>& a, const mat4<F>& b) 
    {
        mat4<F> res;

        for (int col = 0; col < 4; col++) 
        {
            res.columns[col][0] = a.columns[0][0] * b.columns[col][0] + a.columns[1][0] * b.columns[col][1] + a.columns[2][0] * b.columns[col][2] + a.columns[3][0] * b.columns[col][3];
            res.columns[col][1] = a.columns[0][1] * b.columns[col][0] + a.columns[1][1] * b.columns[col][1] + a.columns[2][1] * b.columns[col][2] + a.columns[3][1] * b.columns[col][3];
            res.columns[col][2] = a.columns[0][2] * b.columns[col][0] + a.columns[1][2] * b.columns[col][1] + a.columns[2][2] * b.columns[col][2] + a.columns[3][2] * b.columns[col][3];
            res.columns[col][3] = a.columns[0][3] * b.columns[col][0] + a.columns[1][3] * b.columns[col][1] + a.columns[2][3] * b.columns[col][2] + a.columns[3][3] * b.columns[col][3];
        }

        return res;
    }



    template<FloatingNumber F>
    inline mat4<F> operator+(const mat4<F>& a, const mat4<F>& b)
    {
        mat4<F> res;

        for (int i = 0; i < 16; i++)
        {
            res.indices[i] = a.indices[i] + b.indices[i];
        }

        return res;
    }

    template<FloatingNumber F>
    inline mat4<F> operator-(const mat4<F>& a, const mat4<F>& b)
    {
        mat4<F> res;

        for (int i = 0; i < 16; i++)
        {
            res.indices[i] = a.indices[i] - b.indices[i];
        }

        return res;
    }


    template<FloatingNumber F>
    inline mat4<F> operator*(const mat4<F>& mat, F scalar)
    {
        mat4<F> res;

        for (int i = 0; i < 16; i++)
        {
            res.indices[i] = mat.indices[i] * scalar;
        }

        return res;
    }

    template<FloatingNumber F>
    inline mat4<F> operator*(F scalar, const mat4<F>& mat)
    {
        mat4<F> res;

        for (int i = 0; i < 16; i++)
        {
            res.indices[i] = mat.indices[i] * scalar;
        }

        return res;
    }


    template<FloatingNumber F>
    inline mat4<F> operator/(const mat4<F>& mat, F scalar)
    {
        if (std::abs(scalar) < math::epsilon<F>()) return mat;
        
        
        F invScalar = static_cast<F>(1.0) / scalar;

        mat4<F> res;

        for (int i = 0; i < 16; i++)
        {
            res.indices[i] = mat.indices[i] * invScalar;
        }

        return res;
    }

    #pragma endregion
}
