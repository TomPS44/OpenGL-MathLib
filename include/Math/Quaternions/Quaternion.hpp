#pragma once

#include "Math\Concepts.hpp"


namespace glMath
{
    template<FloatingNumber F>
    struct vec3;

    template<FloatingNumber F>
    struct mat4;

    template<FloatingNumber F>
    struct mat3;

    template<FloatingNumber F>
    struct alignas(sizeof(F) * 4) quat  
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

        inline static quat identity() { return quat(1.0, 0.0, 0.0, 0.0); };
        static quat<F> getPureQuat(const vec3<F>& vec);

        
        inline vec3<F> xyz() const { return vec3<F>(x, y, z); };
        inline vec3<F> zyx() const { return vec3<F>(z, y, x); };


        template<FloatingNumber type>
        quat<type> as() const;


        F* valuePtr() const;

        quat& normalize();
        quat getNormalizedQuat() const;

        quat& conjugate();
        quat getConjugatedQuat() const;

        quat& inverse();
        quat getInvertedQuat() const;

        quat combineLocal(const quat& other) const;
        static quat combineLocal(const quat& a, const quat& b);
        quat combineGlobal(const quat& other) const;
        static quat combineGlobal(const quat& a, const quat& b);

        F length() const;
        F lengthSquared() const;

        static F length(const quat& quat);
        static F lengthSquared(const quat& quat);

        F dotProduct(const quat<F>& other) const;
        static F dotProduct(const quat<F>& a, const quat<F>& b);

        vec3<F> rotatePoint(const vec3<F>& point) const;
        vec3<F> rotatePointAroundPivot(const vec3<F>& point, const vec3<F>& pivot) const;

        static quat fromAxisAngle(const vec3<F> axis, F angle);

        static quat lookAtFree(const vec3<F>& eye, const vec3<F>& target);
        static quat lookAt(const vec3<F>& eye, const vec3<F>& target, const vec3<F>& up);

        static quat fromEuler(const vec3<F>& rotation);
        static quat fromEuler(F vx, F vy, F vz);

        static vec3<F> rotatePoint(const vec3<F>& point, const quat<F>& rot);
        static vec3<F> rotatePointAroundPivot(const vec3<F>& point, const vec3<F> pivot, const quat<F>& rot);

        static quat<F> lerp(const quat<F>& start, const quat<F>& end, F t);
        static quat<F> lerpUnclamped(const quat<F>& start, const quat<F>& end, F t);

        static quat<F> slerp(const quat<F>& start, const quat<F>& end, F t);
        static quat<F> slerpUnclamped(const quat<F>& start, const quat<F>& end, F t);

        vec3<F> toEuler() const;

        mat3<F> toMat3() const;
        mat4<F> toMat4() const;


        quat& operator+=(const quat& other);

        quat& operator-=(const quat& other);

        quat& operator*=(const quat& other);
        quat& operator*=(F scalar);

        quat& operator/=(F scalar);
    };

    template<FloatingNumber F>
    inline quat<F> operator*(const quat<F>& a, const quat<F>& b);

    template<FloatingNumber F>
    inline quat<F> operator+(const quat<F>& a, const quat<F>& b);

    template<FloatingNumber F>
    inline quat<F> operator-(const quat<F>& a, const quat<F>& b);

    template<FloatingNumber F>
    inline quat<F> operator*(const quat<F>& rot, F scalar);

    template<FloatingNumber F>
    inline quat<F> operator*(F scalar, const quat<F>& rot);

    template<FloatingNumber F>
    inline quat<F> operator/(const quat<F>& rot, F scalar);


    template<FloatingNumber F>
    bool operator==(const quat<F>& a, const quat<F>& b);
    template<FloatingNumber F>
    bool operator!=(const quat<F>& a, const quat<F>& b);
}

#include "Math\Quaternions\Quaternion.inl"