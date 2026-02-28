#include <cmath>
#include <concepts>

namespace math
{
    
    #pragma region Constructors

    template<std::floating_point F>
    inline mat2<F>::mat2(F m00, F m01, 
                         F m10, F m11)
    {
        columns[0][0] = m00; columns[0][1] = m10; 
        columns[1][0] = m01; columns[1][1] = m11;
        
    }

    template<std::floating_point F>
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
    
    
    template<std::floating_point F>
    inline mat2<F> mat2<F>::diagonal(F diagonal)
    {
        mat2<F> baseMat;

        baseMat.columns[0][0] = diagonal;
        baseMat.columns[1][1] = diagonal;

        return baseMat;
    }

    template<std::floating_point F>
    inline mat2<F> mat2<F>::identity()
    {
        mat2<F> baseMat;

        F f1 = static_cast<F>(1.0);

        baseMat.columns[0][0] = f1;
        baseMat.columns[1][1] = f1;

        return baseMat;
    }

    #pragma endregion StaticConstructors
    
    #pragma region Casting
    
    template<std::floating_point F>
    template<std::floating_point f>
    inline mat2<f> mat2<F>::as() const
    {
        mat2<f> res;

        res.indices[0] = static_cast<f>(indices[0]);
        res.indices[1] = static_cast<f>(indices[1]);
        res.indices[2] = static_cast<f>(indices[2]);
        res.indices[3] = static_cast<f>(indices[3]);
        

        return res;
    }

    #pragma endregion Casting
    
    #pragma region MemberMethods
    
    template<std::floating_point F>
    template<Number N>
    inline N mat2<F>::determinant() const
    {
        return columns[0][0] * columns[1][1] - columns[0][1] * columns[1][0];
    }

    template<std::floating_point F>
    inline mat2<F>& mat2<F>::inverted()
    {
        F det = this->determinant<F>();

        if (std::abs(det) > math::epsilon<F>()) 
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

    template<std::floating_point F>
    inline mat2<F>& mat2<F>::transposed()
    {
        F m01 = columns[1][0];
        F m10 = columns[0][1];

        columns[0][1] = m01;
        columns[1][0] = m10;

        return *this;
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline mat2<f> mat2<F>::getInvertedMat() const
    {
        mat2<F> mat = *this;
        mat = mat.inverted();

        mat2<f> res;

        res.indices[0] = static_cast<f>(mat.indices[0]);
        res.indices[1] = static_cast<f>(mat.indices[1]);
        res.indices[2] = static_cast<f>(mat.indices[2]);
        res.indices[3] = static_cast<f>(mat.indices[3]);

        return res;
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline mat2<f> mat2<F>::getTransposedMat() const
    {
        mat2<F> mat = *this;
        mat = mat.transposed();

        mat2<f> res;

        res.indices[0] = static_cast<f>(mat.indices[0]);
        res.indices[1] = static_cast<f>(mat.indices[1]);
        res.indices[2] = static_cast<f>(mat.indices[2]);
        res.indices[3] = static_cast<f>(mat.indices[3]);

        return res;
    }

    template<std::floating_point F>
    inline F& mat2<F>::at(int row, int col)
    {
        return columns[col][row];
    }

    template<std::floating_point F>
    inline F mat2<F>::at(int row, int col) const
    {
        return columns[col][row];
    }

    #pragma endregion MemberMethods
    
    #pragma region StaticMethods

    template<std::floating_point F>
    inline mat2<F> mat2<F>::rotateZ(F zAngDeg)
    {
        F cosAng = static_cast<F>(std::cos(zAngDeg * math::degToRad<F>()));
        F sinAng = static_cast<F>(std::sin(zAngDeg * math::radToDeg<F>()));

        return mat2(cosAng, -sinAng,
                    sinAng, cosAng);
    }

    #pragma endregion 

    #pragma region ArithmeticOperators

    template<std::floating_point F>
    inline mat2<F> operator+(const mat2<F>& a, const mat2<F>& b) 
    {
        mat2<F> res;

        res.indices[0] = a.indices[0] + b.indices[0];
        res.indices[1] = a.indices[1] + b.indices[1];
        res.indices[2] = a.indices[2] + b.indices[2];
        res.indices[3] = a.indices[3] + b.indices[3];

        return res;
    }

    template<std::floating_point F>
    inline mat2<F> operator-(const mat2<F>& a, const mat2<F>& b) 
    {
        mat2<F> res;

        res.indices[0] = a.indices[0] - b.indices[0];
        res.indices[1] = a.indices[1] - b.indices[1];
        res.indices[2] = a.indices[2] - b.indices[2];
        res.indices[3] = a.indices[3] - b.indices[3];

        return res;
    }

    template<std::floating_point F>
    inline mat2<F> operator*(const mat2<F>& a, const mat2<F>& b) 
    {
        mat2<F> res;

        res.columns[0][0] = a.columns[0][0] * b.columns[0][0] + a.columns[1][0] * b.columns[0][1];
        res.columns[0][1] = a.columns[0][1] * b.columns[0][0] + a.columns[1][1] * b.columns[0][1];

        res.columns[1][0] = a.columns[0][0] * b.columns[1][0] + a.columns[1][0] * b.columns[1][1];
        res.columns[1][1] = a.columns[0][1] * b.columns[1][0] + a.columns[1][1] * b.columns[1][1];

        return res;
    }

    template<std::floating_point F>
    inline mat2<F> operator*(const mat2<F>& mat, F scalar) 
    {
        mat2<F> res;

        res.indices[0] = mat.indices[0] * scalar;
        res.indices[1] = mat.indices[1] * scalar;
        res.indices[2] = mat.indices[2] * scalar;
        res.indices[3] = mat.indices[3] * scalar;

        return res;
    }

    template<std::floating_point F>
    inline mat2<F> operator*(F scalar, const mat2<F>& mat) 
    {
        mat2<F> res;

        res.indices[0] = mat.indices[0] * scalar;
        res.indices[1] = mat.indices[1] * scalar;
        res.indices[2] = mat.indices[2] * scalar;
        res.indices[3] = mat.indices[3] * scalar;

        return res;
    }

    template<std::floating_point F>
    inline vec2<F> operator*(const mat2<F>& mat, const vec2<F>& vec) 
    {
        vec2<F> res;

        res.x = mat.columns[0][0] * vec.x + mat.columns[1][0] * vec.y;
        res.y = mat.columns[0][1] * vec.x + mat.columns[1][1] * vec.y;

        return res;
    }

    template<std::floating_point F>
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

    #pragma endregion 





}
