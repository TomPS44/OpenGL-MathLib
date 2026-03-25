#include <cmath>
#include <concepts>

#include "Math\MathInternal.hpp"

namespace glMath
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
        std::numeric_limits<f> limit = std::numeric_limits<f>();
        f minLimit = limit.lowest();
        f maxLimit = limit.max();


        mat4<f> res;

        for (int i = 0; i < 16; i++)
        {
            res.indices[i] = std::clamp(static_cast<f>(indices[i]), minLimit, maxLimit);
        }

        return res;
    }

    #pragma endregion

    #pragma region StaticMethods

    template<FloatingNumber F>
    inline mat4<F> mat4<F>::transpose(const mat4<F>& mat)
    {
        return mat.getTransposedMat();
    }
    template<FloatingNumber F>
    inline mat4<F> mat4<F>::inverse(const mat4<F>& mat)
    {
        return mat.getInversedMat();
    }


    template<FloatingNumber F>
    inline mat4<F> mat4<F>::getComatrix(const mat4<F>& mat) 
    {
        return mat.getComatrix();
    }

    template<FloatingNumber F>
    inline mat4<F> mat4<F>::getAdjugate(const mat4<F>& mat) 
    {
        return mat.getAdjugate();
    }


    template<FloatingNumber F>
    inline mat3<F> mat4<F>::getNormalMat(const mat4<F>& mat) 
    {
        return mat.getNormalMat();
    }

    
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
        F ang = xAngDeg * glMath::degToRad<F>();
        F cx = static_cast<F>(std::cos(ang));
        F sx = static_cast<F>(std::sin(ang));

        mat4<F> res = mat4<F>::identity();

        res.columns[1][1] = cx;
        res.columns[2][1] = -sx;
        res.columns[1][2] = sx;
        res.columns[2][2] = cx;

        return res;
    }

    template<FloatingNumber F>
    inline mat4<F> mat4<F>::rotateY(F xAngDeg) 
    {
        F ang = xAngDeg * glMath::degToRad<F>();
        F cx = static_cast<F>(std::cos(ang));
        F sx = static_cast<F>(std::sin(ang));

        mat4<F> res = mat4<F>::identity();

        res.columns[0][0] = cx;
        res.columns[2][0] = sx;
        res.columns[0][2] = -sx;
        res.columns[2][2] = cx;

        return res;
    }

    template<FloatingNumber F>
    inline mat4<F> mat4<F>::rotateZ(F xAngDeg) 
    {
        F ang = xAngDeg * glMath::degToRad<F>();
        F cx = static_cast<F>(std::cos(ang));
        F sx = static_cast<F>(std::sin(ang));

        mat4<F> res = mat4<F>::identity();

        res.columns[0][0] = cx;
        res.columns[1][0] = -sx;
        res.columns[0][1] = sx;
        res.columns[1][1] = cx;

        return res;
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


    template<FloatingNumber F>
    inline mat4<F> mat4<F>::lookAt(const vec3<F>& eye, const vec3<F>& target, const vec3<F>& worldUp)
    {
        F f0 = static_cast<F>(0.0);
        F f1 = static_cast<F>(1.0);
        F f2 = static_cast<F>(2.0);
        F f025 = static_cast<F>(0.25);
        
        vec3<F> forward = (target - eye).getUnitVector();
        vec3<F> right;

        F dotUp = vec3<F>::dotProduct(worldUp, forward);
        if (std::abs(dotUp) > static_cast<F>(0.9999)) 
        { 
            vec3<F> temporaryUp = std::abs(forward.z) < static_cast<F>(0.999) ? vec3<F>(f0, f0, f1) : vec3<F>(f1, f0, f0); 
            right = vec3<F>::crossProduct(temporaryUp, forward).getUnitVector(); 
        } 
        else 
        { 
            right = vec3<F>::crossProduct(worldUp, forward).getUnitVector(); 
        }
            
        vec3<F> actualUp = vec3<F>::crossProduct(forward, right);  
        
        F m00 = right.x;     F m01 = right.y;     F m02 = right.z;
        F m10 = actualUp.x;  F m11 = actualUp.y;  F m12 = actualUp.z;
        F m20 = forward.x;   F m21 = forward.y;   F m22 = forward.z;
            
        mat4<F> res = mat4<F>::identity();

        res.columns[0][0] = right.x;    res.columns[1][0] = right.x;    res.columns[2][0] = right.x;    res.columns[3][0] = -vec3<F>::dotProduct(right, eye);
        res.columns[0][1] = actualUp.x; res.columns[1][0] = actualUp.x; res.columns[2][0] = actualUp.x; res.columns[3][0] = -vec3<F>::dotProduct(actualUp, eye);
        res.columns[0][2] = forward.x;  res.columns[1][0] = forward.x;  res.columns[2][0] = forward.x;  res.columns[3][0] = -vec3<F>::dotProduct(forward, eye);
    
        return res;
    }


    template<FloatingNumber F>
    inline mat4<F> mat4<F>::perspective(F fovInRad, F aspectRatio, F near, F far)
    {
        F f2 = static_cast<F>(2.0);
        F f1 = static_cast<F>(1.0);
        F f05 = static_cast<F>(0.5);

        F tanHalfFOV = std::tan(fovInRad * static_cast<F>(0.5));

        mat4<F> res = mat4<F>::identity();

        res.columns[0][0] = f1 / (aspectRatio * tanHalfFOV);
        res.columns[1][1] = f1 / tanHalfFOV;
        res.columns[2][2] = -((far + near) / (far - near));
        res.columns[3][2] = -((static_cast<F>(2.0) * far * near) / (far - near));
        res.columns[2][3] = -f1;

        return res;
    }

    template<FloatingNumber F>
    inline mat4<F> mat4<F>::orthographic(F left, F right, F bottom, F top, F near, F far)
    {
        F f2 = static_cast<F>(2.0);

        mat4<F> res = mat4<F>::identity();

        res.columns[0][0] = f2 / (right - left);
        res.columns[1][1] = f2 / (top - bottom);
        res.columns[1][1] = f2 / (far - near);

        res.columns[3][0] = -((right + left) / (right - left));
        res.columns[3][0] = -((top + bottom) / (top - bottom));
        res.columns[3][0] = -((far + near) / (far - near));

        return res;
    }


    template<FloatingNumber F>
    inline F mat4<F>::determinant(const mat4<F>& mat)
    {
        return mat.determinant();
    }


    template<FloatingNumber F>
    inline vec4<F> mat4<F>::transformPoint(const mat4<F>& mat, const vec4<F>& point)
    {
        return mat * point;
    }

    #pragma endregion

    #pragma region MemberMethods

    template<FloatingNumber F>
    inline vec4<F> mat4<F>::transformPoint(const vec4<F>& point) const
    {
        return *this * point;
    }


    template <FloatingNumber F>
    inline mat4<F>& mat4<F>::transpose()
    {
        mat4<F> copy = *this;

        columns[0][1] = copy.columns[1][0];
        columns[0][2] = copy.columns[2][0];
        columns[0][3] = copy.columns[3][0];
        columns[1][0] = copy.columns[0][1];
        columns[1][2] = copy.columns[2][1];
        columns[1][3] = copy.columns[3][1];
        columns[2][0] = copy.columns[0][2];
        columns[2][1] = copy.columns[1][2];
        columns[2][3] = copy.columns[3][2];
        columns[3][0] = copy.columns[0][3];
        columns[3][1] = copy.columns[1][3];
        columns[3][2] = copy.columns[2][3];

        return *this;
    }

    template <FloatingNumber F>
    inline mat4<F> mat4<F>::getTransposedMat() const
    {
        mat4<F> copy = *this;

        return copy.transpose();
    }


    template <FloatingNumber F>
    inline mat4<F>& mat4<F>::inverse()
    {
        F det = this->determinant();

        if (std::abs(det) > glMath::epsilon<F>())
        {
            F invDet = static_cast<F>(1.0) / det;

            *this = this->getAdjugate() * invDet;
        }

        return *this;
    }

    template <FloatingNumber F>
    inline mat4<F> mat4<F>::getInversedMat() const
    {
        mat4<F> copy = *this;

        return copy.inverse();
    }

    template<FloatingNumber F>
    inline mat4<F> mat4<F>::getAdjugate() const
    {
        // These values exist to not access multiple times the same element in *this,
        // and they're written in row-major, with indices going from 1-4
        // instead of 0-3, so that I can use them a lot faster (because they are
        // written that way in web pages and books)
        
        F m11 = columns[0][0];
        F m12 = columns[1][0];
        F m13 = columns[2][0];
        F m14 = columns[3][0];
        F m21 = columns[0][1];
        F m22 = columns[1][1];
        F m23 = columns[2][1];
        F m24 = columns[3][1];
        F m31 = columns[0][2];
        F m32 = columns[1][2];
        F m33 = columns[2][2];
        F m34 = columns[3][2];
        F m41 = columns[0][3];
        F m42 = columns[1][3];
        F m43 = columns[2][3];
        F m44 = columns[3][3];


        mat4<F> res;
        

        res.columns[0][0] = + m22 * m33 * m44     
                            + m23 * m34 * m42  
                            + m24 * m32 * m43 
                            - m24 * m33 * m42 
                            - m23 * m32 * m44 
                            - m22 * m34 * m43;

        res.columns[1][0] = - m12 * m33 * m44 
                            - m13 * m34 * m42  
                            - m14 * m32 * m43 
                            + m14 * m33 * m42 
                            + m13 * m32 * m44 
                            + m12 * m34 * m43;

        res.columns[2][0] = + m12 * m23 * m44 
                            + m13 * m24 * m42  
                            + m14 * m22 * m43 
                            - m14 * m23 * m42 
                            - m13 * m22 * m44 
                            - m12 * m24 * m43;
                            
        res.columns[3][0] = - m12 * m23 * m34 
                            - m13 * m24 * m32  
                            - m14 * m22 * m33 
                            + m14 * m23 * m32 
                            + m13 * m22 * m34 
                            + m12 * m24 * m33;


        res.columns[0][1] = - m21 * m33 * m44 
                            - m23 * m34 * m41  
                            - m24 * m31 * m43 
                            + m24 * m33 * m41 
                            + m23 * m31 * m44 
                            + m21 * m34 * m43;

        res.columns[1][1] = + m11 * m33 * m44 
                            + m13 * m34 * m41  
                            + m14 * m31 * m43 
                            - m14 * m33 * m41 
                            - m13 * m31 * m44 
                            - m11 * m34 * m43;

        res.columns[2][1] = - m11 * m23 * m44 
                            - m13 * m24 * m41  
                            - m14 * m21 * m43 
                            + m14 * m23 * m41 
                            + m13 * m21 * m44 
                            + m11 * m24 * m43;

        res.columns[3][1] = + m11 * m23 * m34 
                            + m13 * m24 * m31  
                            + m14 * m21 * m33 
                            - m14 * m23 * m31 
                            - m13 * m21 * m34 
                            - m11 * m24 * m33;


        res.columns[0][2] = + m21 * m32 * m44 
                            + m22 * m34 * m41  
                            + m24 * m31 * m42 
                            - m24 * m32 * m41 
                            - m22 * m31 * m44 
                            - m21 * m34 * m42;

        res.columns[1][2] = - m11 * m32 * m44 
                            - m12 * m34 * m41  
                            - m14 * m31 * m42 
                            + m14 * m32 * m41 
                            + m12 * m31 * m44 
                            + m11 * m34 * m42;

        res.columns[2][2] = + m11 * m22 * m44 
                            + m12 * m24 * m41  
                            + m14 * m21 * m42 
                            - m14 * m22 * m41 
                            - m12 * m21 * m44 
                            - m11 * m24 * m42;

        res.columns[3][2] = - m11 * m22 * m34 
                            - m12 * m24 * m31  
                            - m14 * m21 * m32 
                            + m14 * m22 * m31 
                            + m12 * m21 * m34 
                            + m11 * m24 * m32;


        res.columns[0][3] = - m21 * m32 * m43 
                            - m22 * m33 * m41  
                            - m23 * m31 * m42 
                            + m23 * m32 * m41 
                            + m22 * m31 * m43 
                            + m21 * m33 * m42;

        res.columns[1][3] = + m11 * m32 * m43 
                            + m12 * m33 * m41  
                            + m13 * m31 * m42 
                            - m13 * m32 * m41 
                            - m12 * m31 * m43 
                            - m11 * m33 * m42;

        res.columns[2][3] = - m11 * m22 * m43 
                            - m12 * m23 * m41  
                            - m13 * m21 * m42 
                            + m13 * m22 * m41 
                            + m12 * m21 * m43 
                            + m11 * m23 * m42;

        res.columns[3][3] = + m11 * m22 * m33 
                            + m12 * m23 * m31  
                            + m13 * m21 * m32 
                            - m13 * m22 * m31 
                            - m12 * m21 * m33 
                            - m11 * m23 * m32;

        return res;
    }

    template<FloatingNumber F>
    inline mat4<F> mat4<F>::getComatrix() const
    {
        // These values exist to not access multiple times the same element in *this,
        // and they're written in row-major, with indices going from 1-4
        // instead of 0-3, so that I can use them a lot faster (because they are
        // written that way in web pages and books)
        
        F m11 = columns[0][0];
        F m12 = columns[1][0];
        F m13 = columns[2][0];
        F m14 = columns[3][0];
        F m21 = columns[0][1];
        F m22 = columns[1][1];
        F m23 = columns[2][1];
        F m24 = columns[3][1];
        F m31 = columns[0][2];
        F m32 = columns[1][2];
        F m33 = columns[2][2];
        F m34 = columns[3][2];
        F m41 = columns[0][3];
        F m42 = columns[1][3];
        F m43 = columns[2][3];
        F m44 = columns[3][3];


        mat4<F> res;
        

        res.columns[0][0] = + m22 * m33 * m44     
                            + m23 * m34 * m42  
                            + m24 * m32 * m43 
                            - m24 * m33 * m42 
                            - m23 * m32 * m44 
                            - m22 * m34 * m43;

        res.columns[0][1] = - m12 * m33 * m44 
                            - m13 * m34 * m42  
                            - m14 * m32 * m43 
                            + m14 * m33 * m42 
                            + m13 * m32 * m44 
                            + m12 * m34 * m43;

        res.columns[0][2] = + m12 * m23 * m44 
                            + m13 * m24 * m42  
                            + m14 * m22 * m43 
                            - m14 * m23 * m42 
                            - m13 * m22 * m44 
                            - m12 * m24 * m43;
                            
        res.columns[0][3] = - m12 * m23 * m34 
                            - m13 * m24 * m32  
                            - m14 * m22 * m33 
                            + m14 * m23 * m32 
                            + m13 * m22 * m34 
                            + m12 * m24 * m33;


        res.columns[1][0] = - m21 * m33 * m44 
                            - m23 * m34 * m41  
                            - m24 * m31 * m43 
                            + m24 * m33 * m41 
                            + m23 * m31 * m44 
                            + m21 * m34 * m43;

        res.columns[1][1] = + m11 * m33 * m44 
                            + m13 * m34 * m41  
                            + m14 * m31 * m43 
                            - m14 * m33 * m41 
                            - m13 * m31 * m44 
                            - m11 * m34 * m43;

        res.columns[1][2] = - m11 * m23 * m44 
                            - m13 * m24 * m41  
                            - m14 * m21 * m43 
                            + m14 * m23 * m41 
                            + m13 * m21 * m44 
                            + m11 * m24 * m43;

        res.columns[1][3] = + m11 * m23 * m34 
                            + m13 * m24 * m31  
                            + m14 * m21 * m33 
                            - m14 * m23 * m31 
                            - m13 * m21 * m34 
                            - m11 * m24 * m33;


        res.columns[2][0] = + m21 * m32 * m44 
                            + m22 * m34 * m41  
                            + m24 * m31 * m42 
                            - m24 * m32 * m41 
                            - m22 * m31 * m44 
                            - m21 * m34 * m42;

        res.columns[2][1] = - m11 * m32 * m44 
                            - m12 * m34 * m41  
                            - m14 * m31 * m42 
                            + m14 * m32 * m41 
                            + m12 * m31 * m44 
                            + m11 * m34 * m42;

        res.columns[2][2] = + m11 * m22 * m44 
                            + m12 * m24 * m41  
                            + m14 * m21 * m42 
                            - m14 * m22 * m41 
                            - m12 * m21 * m44 
                            - m11 * m24 * m42;

        res.columns[2][3] = - m11 * m22 * m34 
                            - m12 * m24 * m31  
                            - m14 * m21 * m32 
                            + m14 * m22 * m31 
                            + m12 * m21 * m34 
                            + m11 * m24 * m32;


        res.columns[3][0] = - m21 * m32 * m43 
                            - m22 * m33 * m41  
                            - m23 * m31 * m42 
                            + m23 * m32 * m41 
                            + m22 * m31 * m43 
                            + m21 * m33 * m42;

        res.columns[3][1] = + m11 * m32 * m43 
                            + m12 * m33 * m41  
                            + m13 * m31 * m42 
                            - m13 * m32 * m41 
                            - m12 * m31 * m43 
                            - m11 * m33 * m42;

        res.columns[3][2] = - m11 * m22 * m43 
                            - m12 * m23 * m41  
                            - m13 * m21 * m42 
                            + m13 * m22 * m41 
                            + m12 * m21 * m43 
                            + m11 * m23 * m42;

        res.columns[3][3] = + m11 * m22 * m33 
                            + m12 * m23 * m31  
                            + m13 * m21 * m32 
                            - m13 * m22 * m31 
                            - m12 * m21 * m33 
                            - m11 * m23 * m32;

        return res;
    }

    template<FloatingNumber F>
    inline mat3<F> mat4<F>::getNormalMat() const
    {
        mat3<F> mat3 = {
            columns[0][0], columns[1][0], columns[2][0],
            columns[0][1], columns[1][1], columns[2][1],
            columns[0][2], columns[1][2], columns[2][2],
        };

        return mat3.getInvertedMat().transposed();
    }

    template<FloatingNumber F>
    inline mat3<F> mat4<F>::toMat3() const
    {
        mat3<F> mat3 = {
            columns[0][0], columns[1][0], columns[2][0],
            columns[0][1], columns[1][1], columns[2][1],
            columns[0][2], columns[1][2], columns[2][2],
        };

        return mat3;
    }

    template<FloatingNumber F>
    inline F mat4<F>::determinant() const
    {
        F det = columns[0][0] * this->getMinor(0, 0) -
                columns[1][0] * this->getMinor(0, 1) +
                columns[2][0] * this->getMinor(0, 2) -
                columns[3][0] * this->getMinor(0, 3);

        return det;
    }


    template<FloatingNumber F>
    inline F& mat4<F>::at(int row, int col)
    {
        return columns[col][row];
    }
    template<FloatingNumber F>
    inline const F mat4<F>::at(int row, int col) const
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
    inline F mat4<F>::getMinor(int row, int col) const
    {
        mat3<F> mat = this->getSubmatrix(row, col);

        return mat.determinant();
    }

    template<FloatingNumber F>
    inline F mat4<F>::getCofactor(int row, int col) const
    {
        F minor = this->getMinor(row, col);

        return (row + col) % 2 == 0 ? minor * static_cast<F>(1.0) : minor * static_cast<F>(-1.0);
    }

    #pragma endregion

    #pragma region ReferenceOperators

    template<FloatingNumber F>
    inline mat4<F>& mat4<F>::operator+=(const mat4<F>& other)
    {
        *this = *this + other;
        return *this;
    }
    template<FloatingNumber F>
    inline mat4<F>& mat4<F>::operator+=(F scalar)
    {
        *this = *this + scalar;
        return *this;
    }

    template<FloatingNumber F>
    inline mat4<F>& mat4<F>::operator-=(const mat4<F>& other)
    {
        *this = *this - other;
        return *this;
    }
    template<FloatingNumber F>
    inline mat4<F>& mat4<F>::operator-=(F scalar)
    {
        *this = *this - scalar;
        return *this;
    }

    template<FloatingNumber F>
    inline mat4<F>& mat4<F>::operator*=(const mat4<F>& other)
    {
        *this = *this * other;
        return *this;
    }
    template<FloatingNumber F>
    inline mat4<F>& mat4<F>::operator*=(F scalar)
    {
        *this = *this * scalar;
        return *this;
    }

    template<FloatingNumber F>
    inline mat4<F>& mat4<F>::operator/=(F scalar)
    {
        *this = *this / scalar;
        return *this;
    }

    #pragma endregion


    #pragma region Operators

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
    inline vec4<F> operator*(const mat4<F>& mat, const vec4<F>& vec) 
    {
        return vec4<F>(
            mat.columns[0][0] * vec.x + mat.columns[1][0] * vec.y + mat.columns[2][0] * vec.z + mat.columns[3][0] * vec.w,
            mat.columns[0][1] * vec.x + mat.columns[1][1] * vec.y + mat.columns[2][1] * vec.z + mat.columns[3][1] * vec.w,
            mat.columns[0][2] * vec.x + mat.columns[1][2] * vec.y + mat.columns[2][2] * vec.z + mat.columns[3][2] * vec.w,
            mat.columns[0][3] * vec.x + mat.columns[1][3] * vec.y + mat.columns[2][3] * vec.z + mat.columns[3][3] * vec.w
        );
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
        if (std::abs(scalar) < glMath::epsilon<F>()) return mat;
        
        
        F invScalar = static_cast<F>(1.0) / scalar;

        mat4<F> res;

        for (int i = 0; i < 16; i++)
        {
            res.indices[i] = mat.indices[i] * invScalar;
        }

        return res;
    }



    template<FloatingNumber F>
    inline bool operator==(const mat4<F>& a, const mat4<F>& b)
    {
        for (int i = 0; i < 16; i++)
        {
            if (std::abs(b.indices[i] - a.indices[i]) > glMath::epsilon<F>()) return false;
        }

        return true;
    }

    template<FloatingNumber F>
    inline bool operator!=(const mat4<F>& a, const mat4<F>& b)
    {
        return !(a == b);
    }

    #pragma endregion
}
