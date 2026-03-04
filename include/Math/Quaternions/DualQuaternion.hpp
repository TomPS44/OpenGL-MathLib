#pragma once

#include <concepts>
#include "Math\Concepts.hpp"

namespace math
{
    template<FloatingNumber F>
    struct quat;

    template<FloatingNumber F>
    struct vec3;

    template<FloatingNumber F>
    struct dualQuat
    {
    public:
        quat<F> real;
        quat<F> dual;

    public:
        dualQuat();
        dualQuat(const quat<F>& rotation, const vec3<F>& translation);
        dualQuat(const quat<F>& rotation, const quat<F>& translation);
        dualQuat(const quat<F>& rotation);
        dualQuat(const vec3<F>& translation);
        
        static dualQuat<F> identity();

        template<FloatingNumber type>
        dualQuat<type> as() const;

        quat<F> getRotation() const;

        vec3<F> getTranslation() const;


        dualQuat& normalized();
        dualQuat getUnitDualQuat() const;

        dualQuat& conjugated();
        dualQuat getConjugatedDualQuat() const;

        dualQuat& inversed();
        dualQuat getInversedDualQuat() const;


        mat4<F> toMat4() const;

        static dualQuat<F> lerp(const dualQuat<F>& start, const dualQuat<F>& end, F t);
        static dualQuat<F> lerpUnclamped(const dualQuat<F>& start, const dualQuat<F>& end, F t);

        vec3<F> transformPoint(const vec3<F>& point) const;
        static vec3<F> transformPoint(const vec3<F>& point, const dualQuat<F>& dQuat);
    };

    template<FloatingNumber F>
    dualQuat<F> operator*(const dualQuat<F>& a, const dualQuat<F>& b);

    template<FloatingNumber F>
    dualQuat<F> operator+(const dualQuat<F>& a, const dualQuat<F>& b);

    template<FloatingNumber F>
    dualQuat<F> operator*(const dualQuat<F>& dQuat, F scalar);

    template<FloatingNumber F>
    dualQuat<F> operator*(F scalar, const dualQuat<F>& dQuat);
}

#include "Math\Quaternions\DualQuaternion.inl"