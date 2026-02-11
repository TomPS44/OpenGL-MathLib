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
        vec2() : x(static_cast<F>(0.0)), y(static_cast<F>(0.0)) {}
        // Constructor that returns a vec2 with x being vx, and y being vy 
        vec2(F vx, F vy) : x(vx), y(vy) {}
        // Constructor that returns a vec2 with x being vec.x and y being vec.y
        template<std::floating_point f>
        vec2(const vec2<f>& vec) : x(static_cast<F>(vec.x)), y(static_cast<F>(vec.y)) {}
        // Constructor that returns a vec2 from an angle
        static vec2<F> fromAngle(const angle<F>& angle);
        static vec2 fromAngle(F angleInDeg) 
        {
            return vec2(std::cosf(angleInDeg * math::degToRad<F>()), std::sinf(angleInDeg * math::degToRad<F>()));
        }
    

        
        // Equivalent of Vec2(0.0f, 0.0f)
        template<std::floating_point f>
        static vec2<f> zero() { return vec2(static_cast<f>(0.0), static_cast<f>(0.0)); }
        // Equivalent of Vec2(1.0f, 1.0f)
        template<std::floating_point f>
        static vec2 one() { return vec2(static_cast<f>(1.0), static_cast<f>(1.0)); }
        // Equivalent of Vec2(0.0f, 1.0f)
        template<std::floating_point f>
        static vec2 up() { return vec2(static_cast<f>(0.0), static_cast<f>(1.0)); }
        // Equivalent of Vec2(0.0f, -1.0f)
        template<std::floating_point f>
        static vec2 down() { return vec2(static_cast<f>(0.0), static_cast<f>(-1.0)); }
        // Equivalent of Vec2(-1.0f, 0.0f)
        template<std::floating_point f>
        static vec2 left() { return vec2(static_cast<f>(-1.0), static_cast<f>(0.0)); }
        // Equivalent of Vec2(1.0f, 0.0f)
        template<std::floating_point f>
        static vec2 right() { return vec2(static_cast<f>(1.0), static_cast<f>(0.0)); }

        // Returns a new Vec2 made of the X and Y values of the vector
        template<std::floating_point f>
        vec2 XY() const { return vec2(static_cast<f>(x), static_cast<f>(y)); }
        // Returns a new Vec2 made of the y and X values of the vector
        template<std::floating_point f>
        vec2 YX() const { return vec2(static_cast<f>(y), static_cast<f>(x)); }
        // Returns a new Vec2 made of the X and X values of the vector
        template<std::floating_point f>
        vec2 XX() const { return vec2(static_cast<f>(x), static_cast<f>(x)); }
        // Returns a new Vec2 made of the Y and Y values of the vector
        template<std::floating_point f>
        vec2 YY() const { return vec2(static_cast<f>(y), static_cast<f>(y)); }

        // Returns the same vector, but with its magnitude being 1
        vec2& normalized()
        {
            double l = this->length<double>();
            if (l > 0.0) 
            {
                F inverseLength = static_cast<F>(1.0) / l;

                x *= inverseLength; 
                y *= inverseLength;
            }

            return *this;
        }

        // Returns a new vector, that is the same as the original one, but normalized
        template<std::floating_point f>
        vec2 getUnitVector() const
        {
            vec2 copy = *this;
            copy = copy.normalized();

            copy.x = static_cast<f>(copy.x);
            copy.y = static_cast<f>(copy.y);

            return copy;
        }

        // Returns the magnitude of the vector
        template<Number N>
        N length() const
        {
            return static_cast<N>(std::sqrtf( (x * x) + (y * y) ));
        }
        // Returns the magnitude of the vector, but squared
        template<Number N>
        N lengthSquared() const
        {
            return static_cast<N>((x * x) + (y * y));
        }
        // Returns the dot product of the vector with the one specified as a parameter
        template<Number N>
        N dotProduct(const vec2& other) const
        {
            return static_cast<N>((x * other.x) + (y * other.y)); 
        }
        // Returns the distance between the vector, and the one specified as a parameter
        template<Number N>
        N distance(const vec2& other) const
        {
            return static_cast<N>(std::sqrtf( (other.x - x) * (other.x - x)  +  (other.y - y) * (other.y - y) ));
        }
        // Returns the distance between the vector, and the one specified as a parameter, but squared
        template<Number N>
        N distanceSquared(const vec2& other) const
        {
            return static_cast<N>((other.x - x) * (other.x - x)  +  (other.y - y) * (other.y - y));
        }

        template<Number N>
        static N length(const vec2& vec) 
        {
            return static_cast<N>(std::sqrtf( (vec.x * vec.x) + (vec.y * vec.y) ));
        }
        template<Number N>   
        static N lengthSquared(const vec2& vec) 
        {
            return static_cast<N>((vec.x * vec.x) + (vec.y * vec.y));
        }

        template<Number N>
        static N dotProduct(const vec2& vec1, const vec2& vec2)
        {
            return static_cast<N>((vec1.x * vec2.x) + (vec1.y * vec2.y)); 
        }

        template<Number N>
        static N distance(const vec2& vec1, const vec2& vec2)
        {
            return static_cast<N>(std::sqrtf( (vec1.x - vec2.x) * (vec1.x - vec2.x)  +  (vec1.y - vec2.y) * (vec1.y - vec2.y) ));
        }
        template<Number N>
        static N distanceSquared(const vec2& vec1, const vec2& vec2)
        {
            return static_cast<N>((vec1.x - vec2.x) * (vec1.x - vec2.x)  +  (vec1.y - vec2.y) * (vec1.y - vec2.y));
        }

        template<std::floating_point f>
        static vec2<f> lerp(const vec2& start, const vec2& end, f t)
        {
            t = clamp01<f>(t);
            return vec2(static_cast<f>(start.x + (end.x - start.x) * t), static_cast<f>(start.y + (end.y - start.y) * t));
        }
        template<std::floating_point f>
        static vec2<f> lerpUnclamped(const vec2& start, const vec2& end, f t)
        {
            return vec2(static_cast<f>(start.x + (end.x - start.x) * t), static_cast<f>(start.y + (end.y - start.y) * t));
        }
        

        vec2& operator+=(const vec2& other)
        {
            this->x += other.x;
            this->y += other.y;

            return *this;
        }
        vec2& operator-=(const vec2& other)
        {
            this->x -= other.x;
            this->y -= other.y;

            return *this;
        }
        vec2& operator*=(float scalar)
        {
            this->x *= scalar;
            this->y *= scalar;

            return *this;
        }
        vec2& operator/=(float scalar)
        {
            if (scalar == 0.0f) return *this;

            scalar = 1.0f / scalar;

            this->x *= scalar;
            this->y *= scalar;

            return *this;
        }


        // Returns a float pointer of the vector's value at the specified index (x -> 0, y -> 1)
        // The specified index is clamped between 0 and 1
        F* operator[](int index)
        {
            index = clamp01<int>(index);

            if (index == 0) { return &x; }
            else { return &y; }

        }
        
    };

    // Arithmetic Operators

    template<std::floating_point F>
    inline vec2<F> operator+(const vec2<F>& a, const vec2<F>& b)
    {
        return vec2(a.x + b.x, a.y + b.y);
    }
    template<std::floating_point F>
    inline vec2<F> operator-(const vec2<F>& a, const vec2<F>& b)
    {
        return vec2(a.x - b.x, a.y - b.y);
    }
    template<std::floating_point F>
    inline vec2<F> operator*(const vec2<F>& vec, F scalar)
    {
        return vec2(vec.x * scalar, vec.y * scalar);
    }
    template<std::floating_point F>
    inline vec2<F> operator*(F scalar, const vec2<F>& vec)
    {
        return vec2(vec.x * scalar, vec.y * scalar);
    }
    template<std::floating_point F>
    inline vec2<F> operator/(const vec2<F>& vec, F scalar)
    {
        if (scalar == static_cast<F>(0.0)) return vec;

        scalar = static_cast<F>(1.0f)/ scalar;

        return vec2(vec.x * scalar, vec.y * scalar);
    }

    template<std::floating_point F>
    inline bool operator==(const vec2<F>& a, const vec2<F>& b)
    {
        return static_cast<F>(std::abs(a.x - b.x)) < math::epsilon<F>() && 
               static_cast<F>(std::abs(a.y - b.y)) < math::epsilon<F>();
    }
    template<std::floating_point F>
    inline bool operator!=(const vec2<F>& a, const vec2<F>& b)
    {
        return !(a == b);
    }


    
}