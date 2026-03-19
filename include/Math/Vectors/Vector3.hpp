#pragma once 

#include "Math\Concepts.hpp"

namespace glMath
{
    template<FloatingNumber F>
    struct vec2;

    template<FloatingNumber F>
    struct quat;

    // A struct used to represent a Vector3, with x, y and z components
    template<FloatingNumber F>
    struct vec3
    {
    public:
        union 
        {
            struct { F x, y, z; };
            struct { F r, g, b; };
            F data[3];
        };

    public:
        // Constructor that returns a vec3 with x being 0.0, y being 0.0, z being 0.0
        vec3();
        // Constructor that returns a vec3 with x being scalar, y being scalar, z being scalar
        vec3(F scalar);
        // Constructor that returns a vec3 with x being vx, y being vy and z being vz 
        vec3(F vx, F vy);
        // Constructor that returns a vec3 with x being vx, y being vy and z being 0.0 
        vec3(F vx, F vy, F vz);
        // Constructor that returns a vec3 with x being vec.x, y being vec.y and z being vec.z
        vec3(const vec3& vec);

        // Constructor that returns a vec3 with x being vec.x, y being vec.y and z being 0.0
        vec3(const vec2<F>& xy);
        // Constructor that returns a vec3 with x being vec.x, y being vec.y and z being vz
        vec3(const vec2<F>& xy, F vz);


        inline static vec3 zero()     { return vec3(0.0, 0.0, 0.0); };
        inline static vec3 one()      { return vec3(1.0, 1.0, 1.0); };
        inline static vec3 right()    { return vec3(1.0, 0.0, 0.0); };
        inline static vec3 left()     { return vec3(-1.0, 0.0, 0.0); };
        inline static vec3 up()       { return vec3(0.0, 1.0, 0.0); };
        inline static vec3 down()     { return vec3(0.0, -1.0, 0.0); };
        inline static vec3 forward()  { return vec3(0.0, 0.0, 1.0); };
        inline static vec3 backward() { return vec3(0.0, 0.0, -1.0); };
     

        static vec3 fromQuat(const quat<F>& angle);


        template<FloatingNumber type>
        vec3<type> as() const;

        vec2<F> xx() const { return vec2(x, x); };
        vec2<F> yy() const { return vec2(y, y); };
        vec2<F> zz() const { return vec2(z, z); };
        vec2<F> xy() const { return vec2(x, y); };
        vec2<F> xz() const { return vec2(x, z); };
        vec2<F> yx() const { return vec2(y, x); };
        vec2<F> yz() const { return vec2(y, z); };
        vec2<F> zx() const { return vec2(z, x); };
        vec2<F> zy() const { return vec2(z, y); };

        vec3 xxx() const { return vec3(x, x, x); };
        vec3 yyy() const { return vec3(y, y, y); };
        vec3 zzz() const { return vec3(z, z, z); };
        vec3 zyx() const { return vec3(z, y, x); };


        const F* valuePtr() const;

        F length() const;
        F lengthSquared() const;

        F dotProduct(const vec3& other) const;
        vec3<F> crossProduct(const vec3<F>& other) const;

        F distance(const vec3& other) const;
        F distanceSquared(const vec3& other) const;

        static F length(const vec3& vec);
        static F lengthSquared(const vec3& vec)  ;

        static F dotProduct(const vec3& vec1, const vec3& vec2);

        static vec3 crossProduct(const vec3& a, const vec3& b);

        static F distance(const vec3& vec1, const vec3& vec2);
        static F distanceSquared(const vec3& vec1, const vec3& vec2);

        vec3& normalize();
        vec3 getNormalizedVec() const;
        static vec3 normalized(const vec3& vec);

        vec3 min(const vec3& other) const;
        static vec3 min(const vec3& a, const vec3& b);

        vec3 max(const vec3& other) const;
        static vec3 max(const vec3& a, const vec3& b);

        static vec3 lerp(const vec3& start, const vec3& end, F t);
        static vec3 lerpUnclamped(const vec3& start, const vec3& end, F t);

        static vec3 slerp(const vec3& start, const vec3& end, F t);
        static vec3 slerpUnclamped(const vec3& start, const vec3& end, F t);


        vec3& operator+=(const vec3& other);
        vec3& operator+=(F scalar);
        vec3& operator-=(const vec3& other);
        vec3& operator-=(F scalar);
        vec3& operator*=(const vec3& other);
        vec3& operator*=(F scalar);
        vec3& operator/=(F scalar);

        vec3 operator-() const;
    };

    template<FloatingNumber F>
    inline vec3<F> operator+(const vec3<F>& a, const vec3<F>& b);
    template<FloatingNumber F>
    inline vec3<F> operator+(const vec3<F>& a, F scalar);

    template<FloatingNumber F>
    inline vec3<F> operator-(const vec3<F>& a, const vec3<F>& b);
    template<FloatingNumber F>
    inline vec3<F> operator-(const vec3<F>& a, F scalar);

    template<FloatingNumber F>
    inline vec3<F> operator*(const vec3<F>& a, const vec3<F>& b);
    template<FloatingNumber F>
    inline vec3<F> operator*(const vec3<F>& vec, F scalar);
    template<FloatingNumber F>
    inline vec3<F> operator*(F scalar, const vec3<F>& vec);
    
    template<FloatingNumber F>
    inline vec3<F> operator/(const vec3<F>& vec, F scalar);

    template<FloatingNumber F>
    inline bool operator==(const vec3<F>& a, const vec3<F>& b);
    template<FloatingNumber F>
    inline bool operator!=(const vec3<F>& a, const vec3<F>& b);
}

#include "Math\Vectors\Vector3.inl"
