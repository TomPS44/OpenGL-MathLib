#pragma once

#include <concepts>
#include "Math\Concepts.hpp"

namespace glMath
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
        
        inline static dualQuat identity() { return dualQuat(quat<F>(1.0, 0.0, 0.0, 0.0), quat<F>(0.0, 0.0, 0.0, 0.0)); };

        template<FloatingNumber type>
        dualQuat<type> as() const;

        quat<F> getRotation() const;

        vec3<F> getTranslation() const;


        dualQuat& normalize();
        dualQuat getNormalizedDualQuat() const;
        static dualQuat normalized(const dualQuat& dQuat);

        dualQuat& conjugate();
        dualQuat getConjugatedDualQuat() const;
        static dualQuat conjugated(const dualQuat& dQuat);

        dualQuat& inverse();
        dualQuat getInvertedDualQuat() const;
        static dualQuat inverted(const dualQuat& dQuat);


        dualQuat combineLocal(const dualQuat& other) const;
        static dualQuat combineLocal(const dualQuat& a, const dualQuat& b);
        dualQuat combineGlobal(const dualQuat& other) const;
        static dualQuat combineGlobal(const dualQuat& a, const dualQuat& b);


        mat3<F> toMat3() const;
        mat4<F> toMat4() const;

        static dualQuat<F> lerp(const dualQuat<F>& start, const dualQuat<F>& end, F t);
        static dualQuat<F> lerpUnclamped(const dualQuat<F>& start, const dualQuat<F>& end, F t);

        vec3<F> transformPoint(const vec3<F>& point) const;
        static vec3<F> transformPoint(const vec3<F>& point, const dualQuat<F>& dQuat);


        dualQuat& operator+=(const dualQuat& other);

        dualQuat& operator-=(const dualQuat& other);
        
        dualQuat& operator*=(const dualQuat& other);
        dualQuat& operator*=(F scalar);

        dualQuat& operator/=(F scalar);
    };

    template<FloatingNumber F>
    dualQuat<F> operator*(const dualQuat<F>& a, const dualQuat<F>& b);

    template<FloatingNumber F>
    dualQuat<F> operator+(const dualQuat<F>& a, const dualQuat<F>& b);

    template<FloatingNumber F>
    dualQuat<F> operator*(const dualQuat<F>& dQuat, F scalar);

    template<FloatingNumber F>
    dualQuat<F> operator*(F scalar, const dualQuat<F>& dQuat);


    template<FloatingNumber F>
    bool operator==(const dualQuat<F>& a, const dualQuat<F>& b);
    template<FloatingNumber F>
    bool operator!=(const dualQuat<F>& a, const dualQuat<F>& b);
}

#include "Math\Quaternions\DualQuaternion.inl"