#pragma once

namespace math
{
    template<std::floating_point F>
    struct vec3;

    template<std::floating_point F>
    struct mat4;

    template<std::floating_point F>
    struct mat3;

    template<std::floating_point F>
    struct alignas(16) quat  
    {
    public:
        union 
        {
            struct { F w, x, y, z; };
            F data[4];
        };

    public:
        quat();
        quat(F qw, const vec3<F>& xyz);
        quat(F qw, F qx, F qy, F qz);

        static quat<F> identity();
        static quat<F> getPureQuat(const vec3<F>& vec);
        
        template<std::floating_point type = F>
        vec3<type> XYZ() const;
        template<std::floating_point type = F>
        vec3<type> ZYX() const;
        template<std::floating_point type = F>
        quat<type> WXYZ() const;

        F* valuePtr() const;

        quat& normalized();

        template<std::floating_point type = F>
        quat<type> getUnitQuat() const;

        quat& conjugated();

        template<std::floating_point type = F>
        quat<type> getConjugatedQuat() const;

        quat& inversed();

        template<std::floating_point type = F>
        quat<type> getInversedQuat() const;

        template<Number N = F>
        N length() const;
        template<Number N = F>
        N lengthSquared() const;

        template<Number N = F>
        static N length(const quat& quat);
        template<Number N = F>
        static N lengthSquared(const quat& quat);

        template<Number N = F>
        static N dotProduct(const quat<F>& a, const quat<F>& b);

        vec3<F> rotatePoint(const vec3<F>& point) const;
        vec3<F> rotatePointAroundPivot(const vec3<F>& point, const vec3<F>& pivot) const;

        static quat fromAxisAngle(const vec3<F> axis, F angle);

        static quat lookAt(const vec3<F>& eye, const vec3<F>& target, const vec3<F>& up);

        static quat fromEuler(const vec3<F>& rotation);
        static quat fromEuler(F vx, F vy, F vz);

        static vec3<F> rotatePoint(const vec3<F>& point, const quat<F>& rot);
        static vec3<F> rotatePointAroundPivot(const vec3<F>& point, const vec3<F> pivot, const quat<F>& rot);

        vec3<F> toEuler() const;

        template<std::floating_point f = F>
        mat3<f> toMat3() const;
        template<std::floating_point f = F>
        mat4<f> toMat4() const;
    };

    template<std::floating_point F>
    inline quat<F> operator*(const quat<F>& a, const quat<F>& b);

    template<std::floating_point F>
    inline quat<F> operator*(const quat<F>& rot, F scalar);

    template<std::floating_point F>
    inline quat<F> operator*(F scalar, const quat<F>& rot);
}

#include "Math\Quaternions\Quaternion.inl"