#pragma once 

#include "Math\Concepts.hpp"

namespace math
{
    template<std::floating_point F>
    struct vec2;

    // A struct used to represent a Vector3, with x, y and z components
    template<std::floating_point F>
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

        static vec3 zero();
        static vec3 one();
        static vec3 right();
        static vec3 left();
        static vec3 up();
        static vec3 down();
        static vec3 forward();
        static vec3 backward();


        template<std::floating_point type = F>
        type X() const;
        template<std::floating_point type = F>
        type Y() const;
        template<std::floating_point type = F>
        type Z() const;

        template<std::floating_point type = F>
        vec2<type> XX() const; 
        template<std::floating_point type = F>
        vec2<type> YY() const;
        template<std::floating_point type = F>
        vec2<type> ZZ() const;
        template<std::floating_point type = F>
        vec2<type> XY() const;
        template<std::floating_point type = F>
        vec2<type> XZ() const;
        template<std::floating_point type = F>
        vec2<type> YX() const;
        template<std::floating_point type = F>
        vec2<type> YZ() const;
        template<std::floating_point type = F>
        vec2<type> ZX() const;
        template<std::floating_point type = F>
        vec2<type> ZY() const;

        template<std::floating_point type = F>
        vec3<type> XXX() const;
        template<std::floating_point type = F>
        vec3<type> YYY() const;
        template<std::floating_point type = F>
        vec3<type> ZZZ() const;
        template<std::floating_point type = F>
        vec3<type> XYZ() const;
        template<std::floating_point type = F>
        vec3<type> ZYX() const;


        const F* valuePtr() const;

        template<Number N>
        N length() const;
        template<Number N>
        N lengthSquared() const;

        template<Number N>
        N dotProduct(const vec3& other) const;
        vec3<F> crossProduct(const vec3<F>& other) const;

        template<Number N>
        N distance(const vec3& other) const;
        template<Number N>
        N distanceSquared(const vec3& other) const;

        template<Number N>
        static N length(const vec3& vec);
        template<Number N>
        static N lengthSquared(const vec3& vec)  ;

        template<Number N>
        static N dotProduct(const vec3& vec1, const vec3& vec2);

        static vec3 crossProduct(const vec3& a, const vec3& b);

        template<Number N>
        static N distance(const vec3& vec1, const vec3& vec2);
        template<Number N>
        static N distanceSquared(const vec3& vec1, const vec3& vec2);

        vec3& normalized();

        template<std::floating_point type = F>
        vec3<type> getUnitVector() const;

        template<std::floating_point f>
        static vec3 lerp(const vec3& start, const vec3& end, f t);
        template<std::floating_point f>
        static vec3 lerpUnclamped(const vec3& start, const vec3& end, f t);


        vec3& operator+=(const vec3& other);
        vec3& operator-=(const vec3& other);
        vec3& operator*=(F scalar);
        vec3& operator/=(F scalar);
    };

    template<std::floating_point F>
    inline vec3<F> operator+(const vec3<F>& a, const vec3<F>& b);
    template<std::floating_point F>
    inline vec3<F> operator-(const vec3<F>& a, const vec3<F>& b);
    template<std::floating_point F>
    inline vec3<F> operator*(const vec3<F>& vec, F scalar);
    template<std::floating_point F>
    inline vec3<F> operator*(F scalar, const vec3<F>& vec);
    template<std::floating_point F>
    inline vec3<F> operator/(const vec3<F>& vec, F scalar);

    template<std::floating_point F>
    inline bool operator==(const vec3<F>& a, const vec3<F>& b);
    template<std::floating_point F>
    inline bool operator!=(const vec3<F>& a, const vec3<F>& b);
}

#include "Math\Vectors\Vector3.inl"
