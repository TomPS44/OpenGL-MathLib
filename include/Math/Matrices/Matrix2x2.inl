#include <cmath>
#include <concepts>

#include "Math\MathInternal.hpp"

namespace glMath
{
    
    #pragma region Constructors

    template<FloatingNumber F>
    inline mat2<F>::mat2(F m00, F m01, 
                         F m10, F m11)
    {
        columns[0][0] = m00; columns[0][1] = m10; 
        columns[1][0] = m01; columns[1][1] = m11;
        
    }

    template<FloatingNumber F>
    inline mat2<F>::mat2(F scalar)
    {
        columns[0][0] = scalar; columns[0][1] = scalar; 
        columns[1][0] = scalar; columns[1][1] = scalar;
        
    }

    template<FloatingNumber F>
    inline mat2<F>::mat2()
    {
        F f0 = static_cast<F>(0.0);

        indices[0] = f0;
        indices[1] = f0;
        indices[2] = f0;
        indices[3] = f0;
    }

    #pragma endregion Constructors
    
    #pragma region StaticConstructors
    
    
    template<FloatingNumber F>
    inline mat2<F> mat2<F>::diagonal(F diagonal)
    {
        mat2<F> baseMat;

        baseMat.columns[0][0] = diagonal;
        baseMat.columns[1][1] = diagonal;

        return baseMat;
    }


    #pragma endregion StaticConstructors
    
    #pragma region Casting
    
    template<FloatingNumber F>
    template<FloatingNumber f>
    inline mat2<f> mat2<F>::as() const
    {
        std::numeric_limits<f> limit = std::numeric_limits<f>();
        f minLimit = limit.lowest();
        f maxLimit = limit.max();
        

        mat2<f> res;

        res.indices[0] = std::clamp(static_cast<f>(indices[0]), minLimit, maxLimit);
        res.indices[1] = std::clamp(static_cast<f>(indices[1]), minLimit, maxLimit);
        res.indices[2] = std::clamp(static_cast<f>(indices[2]), minLimit, maxLimit);
        res.indices[3] = std::clamp(static_cast<f>(indices[3]), minLimit, maxLimit);

        return res;
    }

    #pragma endregion Casting
    
    #pragma region MemberMethods
    
    template<FloatingNumber F>
    inline F mat2<F>::determinant() const
    {
        return columns[0][0] * columns[1][1] - columns[0][1] * columns[1][0];
    }

    template<FloatingNumber F>
    inline mat2<F>& mat2<F>::inverse()
    {
        F det = this->determinant();

        if (std::abs(det) > glMath::epsilon<F>()) 
        {
            F invDet = static_cast<F>(1.0) / det;

            F m00 = columns[0][0];
            F m01 = columns[1][0];
            F m10 = columns[0][1];
            F m11 = columns[1][1];

            columns[0][0] =  m11 * invDet;
            columns[0][1] = -m01 * invDet; 
            columns[1][0] = -m10 * invDet;
            columns[1][1] =  m00 * invDet;
        }

        return *this;
    }

    template<FloatingNumber F>
    inline mat2<F>& mat2<F>::transpose()
    {
        F m01 = columns[1][0];
        F m10 = columns[0][1];

        columns[0][1] = m01;
        columns[1][0] = m10;

        return *this;
    }

    template<FloatingNumber F>
    inline mat2<F> mat2<F>::getInvertedMat() const
    {
        mat2<F> res = *this;

        return res.inverse();
    }

    template<FloatingNumber F>
    inline mat2<F> mat2<F>::getTransposedMat() const
    {
        mat2<F> res = *this;

        return res.transpose();
    }

    template<FloatingNumber F>
    inline F& mat2<F>::at(int row, int col)
    {
        return columns[col][row];
    }

    template<FloatingNumber F>
    inline F mat2<F>::at(int row, int col) const
    {
        return columns[col][row];
    }


    template<FloatingNumber F>
    inline vec2<F> mat2<F>::rotatePoint(const mat2<F>& mat, const vec2<F>& point) 
    {
        return mat * point;
    }

    #pragma endregion MemberMethods
    
    #pragma region StaticMethods

    template<FloatingNumber F>
    inline vec2<F> mat2<F>::rotatePoint(const vec2<F>& point) const
    {
        return *this * point;
    }

    template<FloatingNumber F>
    inline F mat2<F>::determinant(const mat2<F>& mat)
    {
        return mat.determinant();
    }

    template<FloatingNumber F>
    inline mat2<F> mat2<F>::inverted(const mat2<F>& mat)
    {
        return mat.getInvertedMat();
    }
    template<FloatingNumber F>
    inline mat2<F> mat2<F>::transposed(const mat2<F>& mat)
    {
        return mat.getTransposedMat();
    }


    template<FloatingNumber F>
    inline mat2<F> mat2<F>::rotateZ(F zAngDeg)
    {
        F cosAng = static_cast<F>(std::cos(zAngDeg * glMath::degToRad<F>()));
        F sinAng = static_cast<F>(std::sin(zAngDeg * glMath::radToDeg<F>()));

        return mat2(cosAng, -sinAng,
                    sinAng, cosAng);
    }

    #pragma endregion
    
    
    #pragma region ReferenceOperators

    template<FloatingNumber F>
    inline mat2<F>& mat2<F>::operator+(const mat2<F>& other)
    {
        return *this + other;
    }
    template<FloatingNumber F>
    inline mat2<F>& mat2<F>::operator+(F scalar)
    {
        return *this + scalar;
    }

    template<FloatingNumber F>
    inline mat2<F>& mat2<F>::operator-(const mat2<F>& other)
    {
        return *this - other;
    }
    template<FloatingNumber F>
    inline mat2<F>& mat2<F>::operator-(F scalar)
    {
        return *this - scalar;
    }

    template<FloatingNumber F>
    inline mat2<F>& mat2<F>::operator*(const mat2<F>& other)
    {
        return *this * other;
    }
    template<FloatingNumber F>
    inline mat2<F>& mat2<F>::operator*(F scalar)
    {
        return *this * scalar;
    }

    template<FloatingNumber F>
    inline mat2<F>& mat2<F>::operator/(F scalar)
    {
        return *this * scalar;
    }

    #pragma endregion


    #pragma region ArithmeticOperators

    template<FloatingNumber F>
    inline mat2<F> operator+(const mat2<F>& a, const mat2<F>& b) 
    {
        mat2<F> res;

        res.indices[0] = a.indices[0] + b.indices[0];
        res.indices[1] = a.indices[1] + b.indices[1];
        res.indices[2] = a.indices[2] + b.indices[2];
        res.indices[3] = a.indices[3] + b.indices[3];

        return res;
    }

    template<FloatingNumber F>
    inline mat2<F> operator-(const mat2<F>& a, const mat2<F>& b) 
    {
        mat2<F> res;

        res.indices[0] = a.indices[0] - b.indices[0];
        res.indices[1] = a.indices[1] - b.indices[1];
        res.indices[2] = a.indices[2] - b.indices[2];
        res.indices[3] = a.indices[3] - b.indices[3];

        return res;
    }

    template<FloatingNumber F>
    inline mat2<F> operator*(const mat2<F>& a, const mat2<F>& b) 
    {
        mat2<F> res;

        res.columns[0][0] = a.columns[0][0] * b.columns[0][0] + a.columns[1][0] * b.columns[0][1];
        res.columns[0][1] = a.columns[0][1] * b.columns[0][0] + a.columns[1][1] * b.columns[0][1];

        res.columns[1][0] = a.columns[0][0] * b.columns[1][0] + a.columns[1][0] * b.columns[1][1];
        res.columns[1][1] = a.columns[0][1] * b.columns[1][0] + a.columns[1][1] * b.columns[1][1];

        return res;
    }

    template<FloatingNumber F>
    inline mat2<F> operator*(const mat2<F>& mat, F scalar) 
    {
        mat2<F> res;

        res.indices[0] = mat.indices[0] * scalar;
        res.indices[1] = mat.indices[1] * scalar;
        res.indices[2] = mat.indices[2] * scalar;
        res.indices[3] = mat.indices[3] * scalar;

        return res;
    }

    template<FloatingNumber F>
    inline mat2<F> operator*(F scalar, const mat2<F>& mat) 
    {
        mat2<F> res;

        res.indices[0] = mat.indices[0] * scalar;
        res.indices[1] = mat.indices[1] * scalar;
        res.indices[2] = mat.indices[2] * scalar;
        res.indices[3] = mat.indices[3] * scalar;

        return res;
    }

    template<FloatingNumber F>
    inline vec2<F> operator*(const mat2<F>& mat, const vec2<F>& vec) 
    {
        vec2<F> res;

        res.x = mat.columns[0][0] * vec.x + mat.columns[1][0] * vec.y;
        res.y = mat.columns[0][1] * vec.x + mat.columns[1][1] * vec.y;

        return res;
    }

    template<FloatingNumber F>
    inline mat2<F> operator/(const mat2<F>& mat, F scalar) 
    {
        if (scalar == static_cast<F>(0.0)) return mat;

        mat2<F> res;

        F invScalar = static_cast<F>(1.0) / scalar;

        res.indices[0] = mat.indices[0] * invScalar;
        res.indices[1] = mat.indices[1] * invScalar;
        res.indices[2] = mat.indices[2] * invScalar;
        res.indices[3] = mat.indices[3] * invScalar;

        return res;
    }


    template<FloatingNumber F>
    inline bool operator==(const mat2<F>& a, const mat2<F>& b) 
    {
        for (int i = 0; i < 4; i++)
        {
            if (std::abs(b.indices[i] - a.indices[i]) > glMath::epsilon<F>())
            {
                return false;
            } 
        }

        return true;
    }

    template<FloatingNumber F>
    inline bool operator!=(const mat2<F>& a, const mat2<F>& b)
    {
        return !(a == b);
    }

    #pragma endregion 





}
