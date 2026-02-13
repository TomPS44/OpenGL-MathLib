#pragma once

#include <cmath>

#include "Math\MathInternal.hpp"

namespace math
{
    template<std::floating_point f>
    struct angle;

    template<std::floating_point F>
    struct vec2
    {
    public:
        union 
        {
            struct { F x, y; };
            F data[2];
        };

    public:
        // Constructor that returns a vec2 with x being 0.0, and y being 0.0 
        vec2();
        // Constructor that returns a vec2 with x being vx, and y being vy 
        vec2(F vx, F vy);
        // Constructor that returns a vec2 with x being vec.x and y being vec.y
        vec2(const vec2<F>& vec);
        // Constructor that returns a vec2 from an angle
        // static vec2<F> fromAngle(const angle<F>& angle);
        // Constructor that returns a vector2 from an angle in RADIANS
        static vec2<F> fromAngle(F angleInDeg);
        
        template<Number N>
        static N angleBetween(const vec2<F>& a, const vec2<F>& b);

        // Equivalent of Vec2(0.0f, 0.0f)
        static vec2 zero();
        // Equivalent of Vec2(1.0f, 1.0f)
        static vec2 one();
        // Equivalent of Vec2(0.0f, 1.0f)
        static vec2 up();
        // Equivalent of Vec2(0.0f, -1.0f)
        static vec2 down();
        // Equivalent of Vec2(-1.0f, 0.0f)
        static vec2 left();
        // Equivalent of Vec2(1.0f, 0.0f)
        static vec2 right();


        template<std::floating_point f>
        f X() const;
        template<std::floating_point f>
        f Y() const;
        // Returns a new Vec2 made of the X and Y values of the vector
        template<std::floating_point f = F>
        vec2<f> XY() const;
        // Returns a new Vec2 made of the y and X values of the vector
        template<std::floating_point f = F>
        vec2<f> YX() const;
        // Returns a new Vec2 made of the X and X values of the vector
        template<std::floating_point f = F>
        vec2<f> XX() const;
        // Returns a new Vec2 made of the Y and Y values of the vector
        template<std::floating_point f = F>
        vec2<f> YY() const;

        // Returns the same vector, but with its magnitude being 1
        vec2& normalized();

        // Returns a new vector, that is the same as the original one, but normalized
        template<std::floating_point f = F>
        vec2<f> getUnitVector() const;
        

        // Returns the magnitude of the vector
        template<Number N>
        N length() const;
        // Returns the magnitude of the vector, but squared
        template<Number N>
        N lengthSquared() const;
        // Returns the dot product of the vector with the one specified as a parameter
        template<Number N>
        N dotProduct(const vec2& other) const;
        // Returns the distance between the vector, and the one specified as a parameter
        template<Number N>
        N distance(const vec2& other) const;
        // Returns the distance between the vector, and the one specified as a parameter, but squared
        template<Number N>
        N distanceSquared(const vec2& other) const;


        template<Number N>
        static N length(const vec2& vec);
        template<Number N>   
        static N lengthSquared(const vec2& vec);
        template<Number N>
        static N dotProduct(const vec2& vec1, const vec2& vec2);
        template<Number N>
        static N distance(const vec2& vec1, const vec2& vec2);
        template<Number N>
        static N distanceSquared(const vec2& vec1, const vec2& vec2);

        static vec2 lerp(const vec2& start, const vec2& end, F t);
        static vec2 lerpUnclamped(const vec2& start, const vec2& end, F t);
        

        vec2& operator+=(const vec2& other);
        vec2& operator-=(const vec2& other);
        vec2& operator*=(F scalar);
        vec2& operator/=(F scalar);


        const F* valuePtr() const;
        
    };

    template<std::floating_point F>
    inline vec2<F> operator+(const vec2<F>& a, const vec2<F>& b);
    template<std::floating_point F>
    inline vec2<F> operator-(const vec2<F>& a, const vec2<F>& b);
    template<std::floating_point F>
    inline vec2<F> operator*(const vec2<F>& vec, F scalar);
    template<std::floating_point F>
    inline vec2<F> operator*(F scalar, const vec2<F>& vec);
    template<std::floating_point F>
    inline vec2<F> operator/(const vec2<F>& vec, F scalar);

    template<std::floating_point F>
    inline bool operator==(const vec2<F>& a, const vec2<F>& b);
    template<std::floating_point F>
    inline bool operator!=(const vec2<F>& a, const vec2<F>& b);
}

#include "Math\Vector2.inl"