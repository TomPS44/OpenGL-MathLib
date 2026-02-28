#include <concepts>
#include <cmath>
#include "DualQuaternion.hpp"


namespace math
{

    #pragma region Constructors

    template<std::floating_point F>
    inline dualQuat<F>::dualQuat()
    {
        F f0 = static_cast<F>(0.0);
        quat<F> quat0;

        real = quat0;
        dual = quat0;
    }

    template<std::floating_point F>
    inline dualQuat<F>::dualQuat(const quat<F>& rotation, const vec3<F>& translation)
    {
        real = rotation;
        dual = static_cast<F>(0.5) * (quat<F>::getPureQuat(translation) * rotation);
    }

    template<std::floating_point F>
    inline dualQuat<F>::dualQuat(const quat<F>& rotation, const quat<F>& translation)
    {
        real = rotation;
        dual = translation;
    }

    template<std::floating_point F>
    inline dualQuat<F>::dualQuat(const quat<F>& rotation)
    {
        F f0 = static_cast<F>(0.0);

        real = rotation;
        dual = quat<F>(f0, f0, f0, f0);
    }

    template<std::floating_point F>
    inline dualQuat<F>::dualQuat(const vec3<F>& translation)
    {
        F f0 = static_cast<F>(0.0);

        real = quat<F>::identity();
        dual = quat<F>(static_cast<F>(0.0), translation.x, translation.y, translation.z);
    }

    #pragma endregion

    #pragma region StaticConstructors

    template<std::floating_point F>
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

    template <std::floating_point F>
    inline dualQuat<F>& dualQuat<F>::normalized()
    {
        F l = real.template length<F>();

        if (std::abs(l) > math::epsilon<F>())
        {
            F invLen = static_cast<F>(1.0) / l;

            real *= invLen;
            dual *= invLen;
        }

        return *this;
    }

    template <std::floating_point F>
    template <std::floating_point f>
    inline dualQuat<f> dualQuat<F>::getUnitDualQuat() const
    {
        dualQuat<F> dQuat = *this;
        dQuat = dQuat.normalized();

        dualQuat<f> res;

        // res.real.w = static_cast<F>(dQuat.real.w);
        // res.real.x = static_cast<F>(dQuat.real.x);
        // res.real.y = static_cast<F>(dQuat.real.y);
        // res.real.z = static_cast<F>(dQuat.real.z);

        // res.dual.w = static_cast<F>(dQuat.dual.w);
        // res.dual.x = static_cast<F>(dQuat.dual.x);
        // res.dual.y = static_cast<F>(dQuat.dual.y);
        // res.dual.z = static_cast<F>(dQuat.dual.z);

        res.real = dQuat.real.template WXYZ<f>();
        res.dual = dQuat.dual.template WXYZ<f>();

        return res;
    }

    template <std::floating_point F>
    inline dualQuat<F>& dualQuat<F>::conjugated()
    {
        real *= static_cast<F>(-1.0);
        dual *= static_cast<F>(-1.0);

        return *this;
    }

    template <std::floating_point F>
    template <std::floating_point f>
    inline dualQuat<f> dualQuat<F>::getConjugatedDualQuat() const
    {
        dualQuat<F> dQuat = *this;
        dQuat = dQuat.conjugated();

        dualQuat<f> res;

        // res.real.w = static_cast<F>(dQuat.real.w);
        // res.real.x = static_cast<F>(dQuat.real.x);
        // res.real.y = static_cast<F>(dQuat.real.y);
        // res.real.z = static_cast<F>(dQuat.real.z);

        // res.dual.w = static_cast<F>(dQuat.dual.w);
        // res.dual.x = static_cast<F>(dQuat.dual.x);
        // res.dual.y = static_cast<F>(dQuat.dual.y);
        // res.dual.z = static_cast<F>(dQuat.dual.z);

        res.real = dQuat.real.template WXYZ<f>();
        res.dual = dQuat.dual.template WXYZ<f>();

        return res;
    }

    // template <std::floating_point F>
    // inline dualQuat<F>& dualQuat<F>::inversed()
    // {
    //     real *= static_cast<F>(-1.0);
    //     dual *= static_cast<F>(-1.0);

    //     return *this;
    // }

    // template <std::floating_point F>
    // template <std::floating_point f>
    // inline dualQuat<f> dualQuat<F>::getInversedDualQuat() const
    // {
    //     dualQuat<F> dQuat = *this;
    //     dQuat = dQuat.conjugated();

    //     dualQuat<f> res;

    //     // res.real.w = static_cast<F>(dQuat.real.w);
    //     // res.real.x = static_cast<F>(dQuat.real.x);
    //     // res.real.y = static_cast<F>(dQuat.real.y);
    //     // res.real.z = static_cast<F>(dQuat.real.z);

    //     // res.dual.w = static_cast<F>(dQuat.dual.w);
    //     // res.dual.x = static_cast<F>(dQuat.dual.x);
    //     // res.dual.y = static_cast<F>(dQuat.dual.y);
    //     // res.dual.z = static_cast<F>(dQuat.dual.z);

    //     res.real = dQuat.real.template WXYZ<f>();
    //     res.dual = dQuat.dual.template WXYZ<f>();

    //     return res;
    // }

    #pragma endregion

    #pragma region Casting

    template<std::floating_point F>
    template<std::floating_point f>
    inline dualQuat<f> dualQuat<F>::as() const
    {
        return dualQuat<f>(real.template WXYZ<f>(), dual.template WXYZ<f>());
    }

    #pragma endregion

    #pragma region MemberMethods

    template < std::floating_point F>
    template < std::floating_point f>
    inline quat < f> dualQuat < F> ::getRotation() const
    {
        return real.template WXYZ<f>();
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec3<f> dualQuat<F>::getTranslation() const
    {
        return ( static_cast<F>(2.0) * (dual * real.getConjugatedQuat()) ).template XYZ<f>();
    }

    

    template<std::floating_point F>
    template<std::floating_point f>
    inline mat4<f> dualQuat<F>::toMat4() const
    {
        F xx = static_cast<f>(real.x * real.x);
        F yy = static_cast<f>(real.y * real.y);
        F zz = static_cast<f>(real.z * real.z);
        F xy = static_cast<f>(real.x * real.y);
        F wz = static_cast<f>(real.w * real.z);
        F wy = static_cast<f>(real.w * real.y);
        F wx = static_cast<f>(real.w * real.x);
        F xz = static_cast<f>(real.x * real.z);
        F yz = static_cast<f>(real.y * real.z);

        F f0 = static_cast<F>(0.0);

        vec3<f> t = this->getTranslation();

        return mat4<f>(1 - 2 * (yy + zz), 2 * (xy - wz)    , 2 * (xz + wy)    , t.x,
                       2 * (xy + wz)    , 1 - 2 * (xx + zz), 2 * (yz - wx)    , t.y,
                       2 * (xz - wy)    , 2 * (yz + wx)    , 1 - 2 * (xx + yy), t.z,
                       f0               , f0               , f0               , static_cast<F>(1.0));
    }

    template<std::floating_point F>
    inline vec3<F> dualQuat<F>::transformPoint(const vec3<F>& point) const
    {
        vec3<F> rotatedPoint = real.rotatePoint(point);
        return vec3<F>(rotatedPoint + this->getTranslation());
    }

    
    #pragma endregion

    #pragma region StaticMethods

    template<std::floating_point F>
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

    template<std::floating_point F>
    inline dualQuat<F> dualQuat<F>::lerpUnclamped(const dualQuat<F>& start, const dualQuat<F>& end, F t) 
    {
        dualQuat<F> trueEnd = end;
        
        if (quat<F>::dotProduct(start.real, end.real) < static_cast<F>(0.0)) 
        {
            trueEnd *= static_cast<F>(-1.0);
        }
        
        dualQuat<F> interp = { (static_cast<F>(1.0) - t) * start, t * trueEnd };
        
        return interp.normalized();
    }
    
    template<std::floating_point F>
    inline vec3<F> dualQuat<F>::transformPoint(const vec3<F>& point, const dualQuat<F>& dQuat) 
    {
        vec3<F> rotatedPoint = dQuat.real.rotatePoint(point);
        return vec3<F>(rotatedPoint + dQuat.getTranslation());
    }
    
    #pragma endregion


    template <std::floating_point F>
    dualQuat<F> operator*(const dualQuat<F>& dQuat, F scalar)
    {
        dualQuat<F> res = dQuat;

        res.real *= scalar;
        res.dual *= scalar;

        return res;
    }

    template <std::floating_point F>
    dualQuat<F> operator*(F scalar, const dualQuat<F>& dQuat)
    {
        dualQuat<F> res = dQuat;

        res.real *= scalar;
        res.dual *= scalar;

        return res;
    }
}