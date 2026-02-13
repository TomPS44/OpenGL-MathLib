#pragma once 

#include <cmath>
#include <concepts>

#include "Math\Concepts.hpp"
#include "Math\MathInternal.hpp"

#include "Math\Angle.hpp"
#include "Math\Vector2.hpp"
#include "Math\Vector3.hpp"
#include "Math\Quaternion.hpp"
#include "Math\Matrix4x4.hpp"
#include "Vector3.hpp"

namespace math
{
    // ----------- Angle.hpp --------------

    template<std::floating_point F>
    inline angle<F> angle<F>::angleBetween(const vec2<F>& a, const vec2<F>& b)
    {
        //
        // Soit v et u des vecteurs
        //
        // v • u = ||v|| ||u|| cos(θ)
        //
        //            (   v • u   )
        //  θ = arccos(-----------)
        //            (||v|| ||u||)
        //
        //          ↑↑↑↑↑↑↑↑↑
        //       comes from here

        F dot = vec2<F>::dotProduct(a.getUnitVector(), b.getUnitVector());

        return angle::fromRadians(std::acos(math::clamp<F>(dot, static_cast<F>(-1.0), static_cast<F>(1.0))));
    }

    // ----------- Vector2.hpp --------------

    // template<std::floating_point F>
    // inline vec2<F> vec2<F>::fromAngle(const angle<F>& angle)
    // { 
    //     return vec2(std::cos(angle.asRadians()), std::sin(angle.asRadians())); 
    // }

    // ----------- Vector3.hpp --------------

    template<std::floating_point F>
    inline vec3<F>::vec3(const vec2<F>& xy) : x(xy.x), y(xy.y), z(static_cast<F>(0.0)) {}
    template<std::floating_point F>
    inline vec3<F>::vec3(const vec2<F>& xy, F vz) : x(xy.x), y(xy.y), z(vz) {}


    // template<std::floating_point F>
    // inline vec2<F> vec3<F>::XX() const { return vec2(y, y); }
    // template<std::floating_point F>
    // inline vec2<F> vec3<F>::YY() const { return vec2(y, y); }
    // template<std::floating_point F>
    // inline vec2<F> vec3<F>::ZZ() const { return vec2(z, z); }
    // template<std::floating_point F>
    // inline vec2<F> vec3<F>::XY() const { return vec2(x, y); }
    // template<std::floating_point F>
    // inline vec2<F> vec3<F>::XZ() const { return vec2(x, z); }
    // template<std::floating_point F>
    // inline vec2<F> vec3<F>::YX() const { return vec2(y, x); }
    // template<std::floating_point F>
    // inline vec2<F> vec3<F>::YZ() const { return vec2(y, z); }
    // template<std::floating_point F>
    // inline vec2<F> vec3<F>::ZX() const { return vec2(z, x); }
    // template<std::floating_point F>
    // inline vec2<F> vec3<F>::ZY() const { return vec2(z, y); }


    // ----------- Quaternion.hpp --------------

    template<std::floating_point F>
    inline quat<F>::quat(F qw, const vec3<F>& xyz) : w(qw), x(xyz.x), y(xyz.y), z(xyz.z) {}

    template<std::floating_point F>
    inline quat<F> quat<F>::fromAxisAngle(vec3<F> axis, F angle)
    {
        axis = axis.normalized();
        F theta = (angle * math::degToRad<F>()) / static_cast<F>(2.0);

        F w = static_cast<F>(std::cos(theta));
        F x = axis.x * static_cast<F>(std::sin(theta));
        F y = axis.y * static_cast<F>(std::sin(theta));
        F z = axis.z * static_cast<F>(std::sin(theta));

        return quat(w, x, y, z);
    }

    template<std::floating_point F>
    inline quat<F> quat<F>::fromEuler(const vec3<F>& rotation)
    {
        // the Hamilton product is still not implemented

        F phi = (rotation.x * math::degToRad<F>()) / static_cast<F>(2.0);
        F theta = (rotation.y * math::degToRad<F>()) / static_cast<F>(2.0);
        F psi = (rotation.z * math::degToRad<F>()) / static_cast<F>(2.0);

        F cosPhi = static_cast<F>(std::cosf(phi));
        F cosTheta = static_cast<F>(std::cosf(theta));
        F cosPsi = static_cast<F>(std::cosf(psi));
        F sinPhi = static_cast<F>(std::sinf(phi));
        F sinTheta = static_cast<F>(std::sinf(theta));
        F sinPsi = static_cast<F>(std::sinf(psi));

        F w = cosPhi * cosTheta * cosPsi + sinPhi * sinTheta * sinPsi;
        F x = sinPhi * cosTheta * cosPsi - cosPhi * sinTheta * sinPsi;
        F y = cosPhi * sinTheta * cosPsi + sinPhi * cosTheta * sinPsi;
        F z = cosPhi * cosTheta * sinPsi - sinPhi * sinTheta * cosPsi;

        return quat(w, x, y, z);
    }

    template<std::floating_point F>
    inline vec3<F> quat<F>::toEuler() const
    {
        F x = static_cast<F>(std::asin(2 * (w * x - x * z)));
        F y = static_cast<F>(std::atan2(2 * (w * x + y * x), 1 - 2 * (x * x + y * y)));
        F z = static_cast<F>(std::atan2(2 * (w * z + x * y), 1 - 2 * (x * x + z * z)));

        return vec3(x, y, z);
    }

    template<std::floating_point F>
    inline quat<F> operator*(const quat<F> &a, const quat<F> &b)
    {
        quat qa = a.getUnitQuat();
        quat qb = b.getUnitQuat();

        F w = qa.w * qb.w - vec2<F>::dotProduct(qa.xyz(), qb.xyz()); 

        vec3 xyz = qb.xyz() * qa.w + qa.xyz() * qb.w + vec3<F>::crossProduct(qa.xyz(), qb.xyz());

        return quat(w, xyz);
    }

    template<std::floating_point F>
    inline mat4 quat<F>::toMat4() const 
    {
        F xx = x * x;
        F yy = y * y;
        F zz = z * z;
        F xy = x * y;
        F wz = w * z;
        F wy = w * y;
        F wx = w * x;
        F xz = x * z;
        F yz = y * z;

        return mat4(1 - 2 * (yy + zz), 2 * (xy - wz)    , 2 * (xz + wy)    , 0.0f,
                    2 * (xy + wz)    , 1 - 2 * (xx + zz), 2 * (yz - wx)    , 0.0f,
                    2 * (xz - wy)    , 2 * (yz + wx)    , 1 - 2 * (xx + yy), 0.0f,
                    0.0f             , 0.0f             , 0.0f             , 1.0f);
    }
}