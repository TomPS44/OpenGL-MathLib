#include <concepts>
#include <cmath>

#include "Math\MathInternal.hpp"

namespace math
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

    #pragma region StaticConstructors

    template<FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::identity()
    {
        F f0 = static_cast<F>(0.0);

        dualQuat<F> res;

        res.real = quat<F>::identity();
        res.dual = quat<F>(f0, f0, f0, f0);

        return res;
    }

    #pragma endregion
    
    #pragma region Normalizing

    template <FloatingNumber F>
    inline dualQuat<F>& dualQuat<F>::normalized()
    {
        F l = real.template length<F>();

        if (std::abs(l) > math::epsilon<F>())
        {
            F invLen = static_cast<F>(1.0) / l;

            real = real * invLen;
            dual = dual * invLen;
        }

        return *this;
    }

    template <FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::getUnitDualQuat() const
    {
        dualQuat<F> copy = *this;

        return copy.normalized();
    }

    template <FloatingNumber F>
    inline dualQuat<F>& dualQuat<F>::conjugated()
    {
        real = real * static_cast<F>(-1.0);
        dual = dual * static_cast<F>(-1.0);

        return *this;
    }

    template <FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::getConjugatedDualQuat() const
    {
        dualQuat<F> copy = *this;

        return copy.conjugated();
    }

    template <FloatingNumber F>
    inline dualQuat<F>& dualQuat<F>::inversed()
    {
        F lSqr2 = real.lengthSquared();

        if (lSqr2 > math::epsilon<F>())
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
    inline dualQuat<F> dualQuat<F>::getInversedDualQuat() const
    {
        dualQuat<F> copy = *this;

        return copy.inversed();
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

        return  ( static_cast<F>(2.0) * (dual * real.getConjugatedQuat()) ).template XYZ();
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

    
    #pragma endregion

    #pragma region StaticMethods

    template<FloatingNumber F>
    inline dualQuat<F> dualQuat<F>::lerp(const dualQuat<F>& start, const dualQuat<F>& end, F t) 
    {
        t = math::clamp01(t);

        #if 0

        dualQuat<F> trueEnd = end;

        if (quat<F>::dotProduct(start.real, end.real) < static_cast<F>(0.0)) 
        {
            trueEnd *= static_cast<F>(-1.0);
        }

        dualQuat<F> interp = { (static_cast<F>(1.0) - t) * start, t * trueEnd };

        return interp.normalized();

        #else 
        
        return dualQuat<F>::lerpUnclamped(start, end, t);

        #endif
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
        
        return interp.normalized();
    }
    
    template<FloatingNumber F>
    inline vec3<F> dualQuat<F>::transformPoint(const vec3<F>& point, const dualQuat<F>& dQuat) 
    {
        vec3<F> rotatedPoint = dQuat.real.rotatePoint(point);
        return vec3<F>(rotatedPoint + dQuat.getTranslation());
    }
    
    #pragma endregion


    template <FloatingNumber F>
    dualQuat<F> operator*(const dualQuat<F>& a, const dualQuat<F>& b)
    {
        dualQuat<F> res;

        res.real = a.real * b.real;
        res.dual = a.real * b.dual + a.dual * b.real;

        return res;
    }

    template <FloatingNumber F>
    dualQuat<F> operator+(const dualQuat<F>& a, const dualQuat<F>& b)
    {
        dualQuat<F> res;

        res.real = a.real + b.real;
        res.dual = a.dual + b.dual;

        return res;
    }

    template <FloatingNumber F>
    dualQuat<F> operator*(const dualQuat<F>& dQuat, F scalar)
    {
        dualQuat<F> res = dQuat;

        res.real = res.real * scalar;
        res.dual = res.dual * scalar;

        return res;
    }

    template <FloatingNumber F>
    dualQuat<F> operator*(F scalar, const dualQuat<F>& dQuat)
    {
        dualQuat<F> res = dQuat;

        res.real = res.real * scalar;
        res.dual = res.dual * scalar;

        return res;
    }
}