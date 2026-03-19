#pragma once

#include "Math\Concepts.hpp"

namespace glMath
{
    template<IntegralNumber I>
    struct iVec2;

    template<FloatingNumber F>
    struct alignas(sizeof(F) * 4) vec2
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
        
        static F angleBetween(const vec2<F>& a, const vec2<F>& b);

        inline static vec2 zero()  { return vec2(0.0, 0.0); };
        inline static vec2 one()   { return vec2(1.0, 1.0); };
        inline static vec2 left()  { return vec2(1.0, 0.0); };
        inline static vec2 right() { return vec2(-1.0, 0.0); };
        inline static vec2 up()    { return vec2(0.0, 1.0); };
        inline static vec2 down()  { return vec2(0.0, -1.0); };


        // Returns a new Vec2 made of the X and Y values of the vector
        template<FloatingNumber f>
        vec2<f> as() const;

        
        template<IntegralNumber type>
        iVec2<type> floorTo() const;
        template<IntegralNumber type>
        iVec2<type> ceilTo() const;
        template<IntegralNumber type>
        iVec2<type> roundTo() const;


        // Returns a new Vec2 made of the y and X values of the vector
        vec2 yx() const { return vec2(y, x); };
        // Returns a new Vec2 made of the X and X values of the vector
        vec2 xx() const { return vec2(x, x); };
        // Returns a new Vec2 made of the Y and Y values of the vector
        vec2 yy() const { return vec2(y, y); };


        // Returns the same vector, but with its magnitude being 1
        vec2& normalize();
        // Returns a new vector, that is the same as the original one, but normalized
        vec2 getNormalizedVec() const;
        static vec2 normalized(const vec2& vec);
        

        // Returns the magnitude of the vector
        F length() const;
        // Returns the magnitude of the vector, but squared
        F lengthSquared() const;
        // Returns the dot product of the vector with the one specified as a parameter
        F dotProduct(const vec2& other) const;
        // Returns the distance between the vector, and the one specified as a parameter
        F distance(const vec2& other) const;
        // Returns the distance between the vector, and the one specified as a parameter, but squared
        F distanceSquared(const vec2& other) const;




        static F length(const vec2& vec);   
        static F lengthSquared(const vec2& vec);
        static F dotProduct(const vec2& vec1, const vec2& vec2);
        static F distance(const vec2& vec1, const vec2& vec2);
        static F distanceSquared(const vec2& vec1, const vec2& vec2);

        vec2 min(const vec2& other) const;
        static vec2 min(const vec2& a, const vec2& b);

        vec2 max(const vec2& other) const;
        static vec2 max(const vec2& a, const vec2& b);

        static vec2 lerp(const vec2& start, const vec2& end, F t);
        static vec2 lerpUnclamped(const vec2& start, const vec2& end, F t);
        static vec2 slerp(const vec2& start, const vec2& end, F t);
        static vec2 slerpUnclamped(const vec2& start, const vec2& end, F t);
        

        vec2& operator+=(const vec2& other);
        vec2& operator-=(const vec2& other);
        vec2& operator*=(F scalar);
        vec2& operator/=(F scalar);

        vec2 operator-() const;


        const F* valuePtr() const;
    };

    template<FloatingNumber F>
    inline vec2<F> operator+(const vec2<F>& a, const vec2<F>& b);
    template<FloatingNumber F>
    inline vec2<F> operator+(const vec2<F>& a, F scalar);

    template<FloatingNumber F>
    inline vec2<F> operator-(const vec2<F>& a, const vec2<F>& b);
    template<FloatingNumber F>
    inline vec2<F> operator-(const vec2<F>& a, F scalar);

    template<FloatingNumber F>
    inline vec2<F> operator*(const vec2<F>& a, const vec2<F>& b);
    template<FloatingNumber F>
    inline vec2<F> operator*(const vec2<F>& vec, F scalar);
    template<FloatingNumber F>
    inline vec2<F> operator*(F scalar, const vec2<F>& vec);

    template<FloatingNumber F>
    inline vec2<F> operator/(const vec2<F>& vec, F scalar);

    template<FloatingNumber F>
    inline bool operator==(const vec2<F>& a, const vec2<F>& b);
    template<FloatingNumber F>
    inline bool operator!=(const vec2<F>& a, const vec2<F>& b);
}

#include "Math\Vectors\Vector2.inl"