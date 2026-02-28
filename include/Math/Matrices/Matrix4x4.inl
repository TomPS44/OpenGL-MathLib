#include <cmath>
#include <concepts>

namespace math
{
    template<std::floating_point F>
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

    template<std::floating_point F>
    inline mat4<F>::mat4()
    {
        for (int i = 0; i < 16; i++)
        {
            indices[i] = static_cast<F>(0.0);
        }
    }


    template<std::floating_point F>
    template<std::floating_point f>
    inline mat4<f> mat4<F>::as() const
    {
        mat4<f> res;

        for (int i = 0; i < 16; i++)
        {
            res.indices[i] = static_cast<f>(indices[i]);
        }

        return res;
    }

    template<std::floating_point F>
    inline mat4<F> mat4<F>::diagonal(F diagonal)
    {
        mat4<F> baseMat;

        baseMat.columns[0][0] = diagonal;
        baseMat.columns[1][1] = diagonal;
        baseMat.columns[2][2] = diagonal;
        baseMat.columns[3][3] = diagonal;

        return baseMat;
    }

    template<std::floating_point F>
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

    template<std::floating_point F>
    inline F& mat4<F>::at(int row, int col)
    {
        return columns[col][row];
    }
    template<std::floating_point F>
    inline F mat4<F>::at(int row, int col) const
    {
        return columns[col][row];
    }

    template<std::floating_point F>
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
}
