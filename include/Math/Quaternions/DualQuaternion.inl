#include <concepts>
#include <cmath>

#include "Math\MathInternal.hpp"

namespace glMath
{

    #pragma region Constructors

    template<FloatingNumber F>
    inline dualQuat<F>::dualQuat()
    {
        quat<F> quat0;

        real = quat0;
        dual = quat0;
    }

    template<FloatingNumber F>
    inline dualQuat<F>::dualQuat(const quat<F>& rotation, const vec3<F>& translation)
    {
        real = rotation;
        dual = static_cast<F>(0.5) * (quat<F>::getPureQuat(translation) * rotation);
    }

    template<FloatingNumber F>
    inline dualQuat<F>::dualQuat(const quat<F>& rotation, const quat<F>& translation)
    {
        real = rotation;
        dual = translation;
    }

    template<FloatingNumber F>
    inline dualQuat<F>::dualQuat(const quat<F>& rotation)
    {
        F f0 = static_cast<F>(0.0);

        real = rotation;
        dual = quat<F>(f0, f0, f0, f0);
    }

    template<FloatingNumber F>
    inline dualQuat<F>::dualQuat(const vec3<F>& translation)
    {
        F f0 = static_cast<F>(0.0);
        F f05 = static_cast<F>(0.5);

        real = quat<F>::identity();
        dual = quat<F>(static_cast<F>(0.0), translation.x * f05, translation.y * f05, translation.z * f05);
    }

    #pragma endregion
    
    #pragma region Normalizing

    template <FloatingNumber F>
    inline dualQuat<F>& dualQuat<F>::normalize()
    {
        F l = real.length();

        if (std::abs(l) > glMath::epsilon<F>())
        {
            F invLen = static_cast<F>(1.0) / l;

            real = real * invLen;
            dual = dual * invLen;
        }

        return *this;
    }

    template <FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::getNormalizedDualQuat() const
    {
        dualQuat<F> copy = *this;

        return copy.normalize();
    }

    template<FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::normalized(const dualQuat<F>& dQuat)
    {
        return dQuat.getNormalizedDualQuat();
    }


    template <FloatingNumber F>
    inline dualQuat<F>& dualQuat<F>::conjugate()
    {
        real = real * static_cast<F>(-1.0);
        dual = dual * static_cast<F>(-1.0);

        return *this;
    }

    template <FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::getConjugatedDualQuat() const
    {
        dualQuat<F> copy = *this;

        return copy.conjugate();
    }

    template<FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::conjugated(const dualQuat<F>& dQuat)
    {
        return dQuat.getConjugatedDualQuat();
    }


    template <FloatingNumber F>
    inline dualQuat<F>& dualQuat<F>::inverse()
    {
        F lSqr2 = real.lengthSquared();

        if (lSqr2 > glMath::epsilon<F>())
        {
            F lSqr4 = lSqr2 * lSqr2;

            F invl2 = static_cast<F>(1.0) / lSqr2;
            F invl4 = invl2 * invl2;

            quat<F> conjReal = real.getConjugatedQuat();
            quat<F> invConjReal = conjReal * static_cast<F>(-1.0);

            quat<F> invReal = conjReal * invl2;
            quat<F> invDual = (invConjReal * dual * conjReal) * invl4;

            this->real = invReal;
            this->dual = invDual;
        }

        return *this;
    }

    template <FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::getInvertedDualQuat() const
    {
        dualQuat<F> copy = *this;

        return copy.inverse();
    }

    template<FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::inverted(const dualQuat<F>& dQuat)
    {
        return dQuat.getInvertedDualQuat();
    }

    #pragma endregion

    #pragma region Casting

    template<FloatingNumber F>
    template<FloatingNumber f>
    inline dualQuat<f> dualQuat<F>::as() const
    {
        return dualQuat<f>(real.template as<f>(), dual.template as<f>());
    }

    #pragma endregion

    #pragma region MemberMethods

    template<FloatingNumber F>
    inline quat<F> dualQuat<F>::getRotation() const
    {
        return real;
    }

    template<FloatingNumber F>
    inline vec3<F> dualQuat<F>::getTranslation() const
    {

        return  ( static_cast<F>(2.0) * (dual * real.getConjugatedQuat()) ).template xyz();
    }


    template<FloatingNumber F>
    inline mat3<F> dualQuat<F>::toMat3() const
    {
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


        return mat3<F>(1 - 2 * (yy + zz), 2 * (xy - wz)    , 2 * (xz + wy),
                       2 * (xy + wz)    , 1 - 2 * (xx + zz), 2 * (yz - wx),
                       2 * (xz - wy)    , 2 * (yz + wx)    , 1 - 2 * (xx + yy)
        );
    }

    template<FloatingNumber F>
    inline mat4<F> dualQuat<F>::toMat4() const
    {
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

        vec3<F> t = this->getTranslation();

        return mat4<F>(1 - 2 * (yy + zz), 2 * (xy - wz)    , 2 * (xz + wy)    , t.x,
                       2 * (xy + wz)    , 1 - 2 * (xx + zz), 2 * (yz - wx)    , t.y,
                       2 * (xz - wy)    , 2 * (yz + wx)    , 1 - 2 * (xx + yy), t.z,
                       f0               , f0               , f0               , static_cast<F>(1.0));
    }

    template<FloatingNumber F>
    inline vec3<F> dualQuat<F>::transformPoint(const vec3<F>& point) const
    {
        vec3<F> rotatedPoint = real.rotatePoint(point);
        return vec3<F>(rotatedPoint + this->getTranslation());
    }

    template<FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::combineLocal(const dualQuat<F>& other) const
    {
        return (*this * other).getNormalizedDualQuat();
    }
    template<FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::combineGlobal(const dualQuat<F>& other) const
    {
        return (other * *this).getNormalizedDualQuat();
    }

    #pragma endregion

    #pragma region StaticMethods


    
    template<FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::combineLocal(const dualQuat<F>& a, const dualQuat<F>& b)
    {
        return (a * b).getNormalizedDualQuat();
    }
    template<FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::combineGlobal(const dualQuat<F>& a, const dualQuat<F>& b)
    {
        return (b * a).getNormalizedDualQuat();
    }


    template<FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::lerp(const dualQuat<F>& start, const dualQuat<F>& end, F t) 
    {
        t = glMath::clamp01(t);

        return dualQuat<F>::lerpUnclamped(start, end, t);
    }

    template<FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::lerpUnclamped(const dualQuat<F>& start, const dualQuat<F>& end, F t) 
    {
        dualQuat<F> trueEnd = end;
        
        if (quat<F>::dotProduct(start.real, end.real) < static_cast<F>(0.0)) 
        {
            trueEnd = trueEnd * static_cast<F>(-1.0);
        }
        
        dualQuat<F> interp = (static_cast<F>(1.0) - t) * start + t * trueEnd;
        
        return interp.normalize();
    }
    
    template<FloatingNumber F>
    inline vec3<F> dualQuat<F>::transformPoint(const vec3<F>& point, const dualQuat<F>& dQuat) 
    {
        vec3<F> rotatedPoint = dQuat.real.rotatePoint(point);
        return vec3<F>(rotatedPoint + dQuat.getTranslation());
    }
    
    #pragma endregion


    #pragma region ReferenceOperators

    template<FloatingNumber F>
    inline dualQuat<F>& dualQuat<F>::operator+=(const dualQuat<F>& other)
    {
        *this = *this + other;
        return *this;
    }

    template<FloatingNumber F>
    inline dualQuat<F>& dualQuat<F>::operator-=(const dualQuat<F>& other)
    {
        *this = *this - other;
        return *this;
    }


    template<FloatingNumber F>
    inline dualQuat<F>& dualQuat<F>::operator*=(const dualQuat<F>& other)
    {
        *this = *this * other;
        return *this;
    }
    template<FloatingNumber F>
    inline dualQuat<F>& dualQuat<F>::operator*=(F scalar)
    {
        *this = *this * scalar;
        return *this;
    }

    template<FloatingNumber F>
    inline dualQuat<F>& dualQuat<F>::operator/=(F scalar)
    {
        *this = *this / scalar;
        return *this;
    }

    #pragma endregion

    #pragma region Operators
    
    template <FloatingNumber F>
    inline dualQuat<F> operator*(const dualQuat<F>& a, const dualQuat<F>& b)
    {
        dualQuat<F> res;

        res.real = a.real * b.real;
        res.dual = a.real * b.dual + a.dual * b.real;
        
        return res;
    }

    template <FloatingNumber F>
    inline dualQuat<F> operator+(const dualQuat<F>& a, const dualQuat<F>& b)
    {
        dualQuat<F> res;

        res.real = a.real + b.real;
        res.dual = a.dual + b.dual;

        return res;
    }

    template <FloatingNumber F>
    inline dualQuat<F> operator*(const dualQuat<F>& dQuat, F scalar)
    {
        dualQuat<F> res = dQuat;

        res.real = res.real * scalar;
        res.dual = res.dual * scalar;

        return res;
    }

    template <FloatingNumber F>
    inline dualQuat<F> operator*(F scalar, const dualQuat<F>& dQuat)
    {
        dualQuat<F> res = dQuat;

        res.real = res.real * scalar;
        res.dual = res.dual * scalar;
        
        return res;
    }


    template<FloatingNumber F>
    inline bool operator==(const dualQuat<F>& a, const dualQuat<F>& b)
    {
        return std::abs(a.real.w - b.real.w) < glMath::epsilon<F>() && 
               std::abs(a.real.x - b.real.x) < glMath::epsilon<F>() && 
               std::abs(a.real.y - b.real.y) < glMath::epsilon<F>() &&
               std::abs(a.real.z - b.real.z) < glMath::epsilon<F>() &&

               std::abs(a.dual.w - b.dual.w) < glMath::epsilon<F>() && 
               std::abs(a.dual.x - b.dual.x) < glMath::epsilon<F>() && 
               std::abs(a.dual.y - b.dual.y) < glMath::epsilon<F>() &&
               std::abs(a.dual.z - b.dual.z) < glMath::epsilon<F>();
    }
    template<FloatingNumber F>
    inline bool operator!=(const dualQuat<F>& a, const dualQuat<F>& b)
    {
        return !(a == b);
    }

    #pragma endregion
}