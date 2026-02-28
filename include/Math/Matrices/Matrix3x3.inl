#include <cmath>
#include <concepts>

namespace math
{
    
    #pragma region Constructors

    template<std::floating_point F>
    inline mat3<F>::mat3(F m00, F m01, F m02, 
                         F m10, F m11, F m12,
                         F m20, F m21, F m22)
    {
        columns[0][0] = m00; columns[0][1] = m10; columns[0][2] = m20;
        columns[1][0] = m01; columns[1][1] = m11; columns[1][2] = m21;
        columns[2][0] = m02; columns[2][1] = m12; columns[2][2] = m22;
    }

    template<std::floating_point F>
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

    #pragma endregion Constructors
    
    #pragma region StaticConstructors
    
    
    template<std::floating_point F>
    inline mat3<F> mat3<F>::diagonal(F diagonal)
    {
        mat3<F> baseMat;

        baseMat.columns[0][0] = diagonal;
        baseMat.columns[1][1] = diagonal;
        baseMat.columns[2][2] = diagonal;

        return baseMat;
    }

    template<std::floating_point F>
    inline mat3<F> mat3<F>::identity()
    {
        mat3<F> baseMat;

        F f1 = static_cast<F>(1.0);

        baseMat.columns[0][0] = f1;
        baseMat.columns[1][1] = f1;
        baseMat.columns[2][2] = f1;

        return baseMat;
    }

    #pragma endregion StaticConstructors
    
    #pragma region Casting
    
    template<std::floating_point F>
    template<std::floating_point f>
    inline mat3<f> mat3<F>::toMat() const
    {
        mat3<f> res;

        res.indices[0] = static_cast<f>(indices[0]);
        res.indices[1] = static_cast<f>(indices[1]);
        res.indices[2] = static_cast<f>(indices[2]);
        res.indices[3] = static_cast<f>(indices[3]);
        res.indices[4] = static_cast<f>(indices[4]);
        res.indices[5] = static_cast<f>(indices[5]);
        res.indices[6] = static_cast<f>(indices[6]);
        res.indices[7] = static_cast<f>(indices[7]);
        res.indices[8] = static_cast<f>(indices[8]);
        
        return res;
    }

    #pragma endregion Casting
    
    #pragma region MemberMethods
    
    template<std::floating_point F>
    template<Number N>
    inline N mat3<F>::determinant() const
    {
        return columns[0][0] * (columns[1][1] * columns[2][2] - columns[2][1] * columns[1][2]) - 
               columns[1][0] * (columns[0][1] * columns[2][2] - columns[0][2] * columns[2][1]) + 
               columns[2][0] * (columns[0][1] * columns[1][2] - columns[1][1] * columns[0][2]);
    }

    template<std::floating_point F>
    inline mat3<F>& mat3<F>::inverted()
    {
        F det = this->determinant<F>();
    
        if (std::abs(det) > math::epsilon<F>()) 
        { 
            #if 0
            *this = this->getAdjugateMat<F>() * (static_cast<F>(1.0) / det);
            #else
            *this = ( this->getComatrix().getTransposedMat() ) * ( static_cast<F>(1.0) / det );
            #endif
        }

        return *this;
    }

    template<std::floating_point F>
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

    template<std::floating_point F>
    template<std::floating_point f>
    inline mat3<f> mat3<F>::getInvertedMat() const
    {
        mat3<F> mat = *this;
        mat = mat.inverted();

        mat3<f> res;

        res.indices[0] = static_cast<f>(mat.indices[0]);
        res.indices[1] = static_cast<f>(mat.indices[1]);
        res.indices[2] = static_cast<f>(mat.indices[2]);
        res.indices[3] = static_cast<f>(mat.indices[3]);
        res.indices[4] = static_cast<f>(mat.indices[4]);
        res.indices[5] = static_cast<f>(mat.indices[5]);
        res.indices[6] = static_cast<f>(mat.indices[6]);
        res.indices[7] = static_cast<f>(mat.indices[7]);
        res.indices[8] = static_cast<f>(mat.indices[8]);

        return res;
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline mat3<f> mat3<F>::getTransposedMat() const
    {
        mat3<F> mat = *this;
        mat = mat.transposed();

        mat3<f> res;

        res.indices[0] = static_cast<f>(mat.indices[0]);
        res.indices[1] = static_cast<f>(mat.indices[1]);
        res.indices[2] = static_cast<f>(mat.indices[2]);
        res.indices[3] = static_cast<f>(mat.indices[3]);
        res.indices[4] = static_cast<f>(mat.indices[4]);
        res.indices[5] = static_cast<f>(mat.indices[5]);
        res.indices[6] = static_cast<f>(mat.indices[6]);
        res.indices[7] = static_cast<f>(mat.indices[7]);
        res.indices[8] = static_cast<f>(mat.indices[8]);

        return res;
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline mat3<f> mat3<F>::getComatrix() const
    {
        #if 0
        
        F m00 = + ( columns[1][1] * columns[2][2] - columns[2][1] * columns[1][2] );
        F m01 = - ( columns[1][0] * columns[2][2] - columns[2][0] * columns[1][2] );
        F m02 = + ( columns[1][0] * columns[2][1] - columns[2][0] * columns[1][1] );

        F m10 = - ( columns[0][1] * columns[2][2] - columns[2][1] * columns[0][2] );
        F m11 = + ( columns[0][0] * columns[1][1] - columns[2][0] * columns[0][2] );
        F m12 = - ( columns[0][0] * columns[2][1] - columns[2][0] * columns[0][1] );

        F m20 = + ( columns[0][1] * columns[1][2] - columns[1][1] * columns[0][2] );
        F m21 = - ( columns[0][0] * columns[1][2] - columns[1][0] * columns[0][2] );
        F m22 = + ( columns[0][0] * columns[1][1] - columns[1][0] * columns[0][1] );


        mat3<f> res;

        res.columns[0][0] = static_cast<f>(m00);
        res.columns[0][1] = static_cast<f>(m01);
        res.columns[0][2] = static_cast<f>(m02);
        res.columns[1][0] = static_cast<f>(m10);
        res.columns[1][1] = static_cast<f>(m11);
        res.columns[1][2] = static_cast<f>(m12);
        res.columns[2][0] = static_cast<f>(m20);
        res.columns[2][1] = static_cast<f>(m21);
        res.columns[2][2] = static_cast<f>(m22);

        return res;
        
        #else

        mat3<f> res;

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

        #endif
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline mat3<f> mat3<F>::getAdjugateMat() const 
    {
        mat3<f> res;

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

    template<std::floating_point F>
    inline F& mat3<F>::at(int row, int col)
    {
        return columns[col][row];
    }

    template<std::floating_point F>
    inline F mat3<F>::at(int row, int col) const
    {
        return columns[col][row];
    }

    // TODO:
    // ↓↓↓↓↓↓↓↓↓↓↓↓↓

    template<std::floating_point F>
    template<Number N>
    inline N mat3<F>::getMinor(int row, int col) const
    {
        
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline mat2<f> mat3<F>::getSubmatrix(int row, int col) const
    {
        
    }

    #pragma endregion MemberMethods
    
    #pragma region StaticMethods

    template<std::floating_point F>
    inline mat3<F> mat3<F>::rotateX(F zAngDeg)
    {
        F ang = zAngDeg * math::degToRad<F>();
        F cosAng = static_cast<F>(std::cos(ang));
        F sinAng = static_cast<F>(std::sin(ang));

        mat3<F> res = mat3<F>::identity();


                                  res.columns[1][1] = cosAng; res.columns[2][1] = -sinAng;
                                  res.columns[1][2] = sinAng; res.columns[2][2] = cosAng;
    
        return res;
    }

    template<std::floating_point F>
    inline mat3<F> mat3<F>::rotateY(F zAngDeg)
    {
        F ang = zAngDeg * math::degToRad<F>();
        F cosAng = static_cast<F>(std::cos(ang));
        F sinAng = static_cast<F>(std::sin(ang));

        mat3<F> res = mat3<F>::identity();

        res.columns[0][0] = cosAng;                            res.columns[2][0] = sinAng;

        res.columns[0][2] = -sinAng;                           res.columns[2][2] = cosAng;

        return res;
    }

    template<std::floating_point F>
    inline mat3<F> mat3<F>::rotateZ(F zAngDeg)
    {
        F ang = zAngDeg * math::degToRad<F>();
        F cosAng = static_cast<F>(std::cos(ang));
        F sinAng = static_cast<F>(std::sin(ang));

        mat3<F> res = mat3<F>::identity();

        res.columns[0][0] = cosAng; res.columns[1][0] = -sinAng;
        res.columns[0][1] = sinAng; res.columns[1][1] = cosAng;

        return res;
    }

    template<std::floating_point F>
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

    #pragma region ArithmeticOperators

    template<std::floating_point F>
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

    template<std::floating_point F>
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

    template<std::floating_point F>
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

    template<std::floating_point F>
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

    template<std::floating_point F>
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

    template<std::floating_point F>
    inline vec3<F> operator*(const mat3<F>& mat, const vec3<F>& vec) 
    {
        return vec3<F>(
        mat.columns[0][0] * vec.x + mat.columns[1][0] * vec.y + mat.columns[2][0] * vec.z,
        mat.columns[0][1] * vec.x + mat.columns[1][1] * vec.y + mat.columns[2][1] * vec.z,
        mat.columns[0][2] * vec.x + mat.columns[1][2] * vec.y + mat.columns[2][2] * vec.z
        );
    }

    template<std::floating_point F>
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

    #pragma endregion 
}
