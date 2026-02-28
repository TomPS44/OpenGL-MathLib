#pragma once

#include <concepts>

namespace math
{
    template<std::floating_point F>
    struct quat;

    template<std::floating_point F>
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

        template<std::floating_point type>
        dualQuat<type> as() const;

        template<std::floating_point type = F>
        quat<type> getRotation() const;

        template<std::floating_point type = F>
        vec3<type> getTranslation() const;


        dualQuat& normalized();

        template<std::floating_point type = F>
        dualQuat<type> getUnitDualQuat() const;

        dualQuat& conjugated();

        template<std::floating_point type = F>
        dualQuat<type> getConjugatedDualQuat() const;

        // dualQuat& inversed();

        // template<std::floating_point type = F>
        // dualQuat<type> getInversedDualQuat() const;


        template<std::floating_point type = F>
        mat4<type> toMat4() const;

        static dualQuat<F> lerp(const dualQuat<F>& start, const dualQuat<F>& end, F t);
        static dualQuat<F> lerpUnclamped(const dualQuat<F>& start, const dualQuat<F>& end, F t);

        vec3<F> transformPoint(const vec3<F>& point) const;
        static vec3<F> transformPoint(const vec3<F>& point, const dualQuat<F>& dQuat);
    };

    template<std::floating_point F>
    dualQuat<F> operator*(const dualQuat<F>& a, const dualQuat<F>& b);

    template<std::floating_point F>
    dualQuat<F> operator+(const dualQuat<F>& a, const dualQuat<F>& b);

    template<std::floating_point F>
    dualQuat<F> operator*(const dualQuat<F>& dQuat, F scalar);

    template<std::floating_point F>
    dualQuat<F> operator*(F scalar, const dualQuat<F>& dQuat);
}

#include "Math\Quaternions\DualQuaternion.inl"