#pragma once 

#include <cmath>
#include <concepts>

#include "Math\MathInternal.hpp"
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
        vec3() : x(static_cast<F>(0.0)), y(static_cast<F>(0.0)), z(static_cast<F>(0.0)) {}
        // Constructor that returns a vec3 with x being vx, y being vy and z being vz 
        vec3(F vx, F vy) : x(vx), y(vy), z(static_cast<F>(0.0)) {}
        // Constructor that returns a vec3 with x being vx, y being vy and z being 0.0 
        vec3(F vx, F vy, F vz) : x(vx), y(vy), z(vz) {}
        // Constructor that returns a vec3 with x being vec.x, y being vec.y and z being vec.z
        vec3(const vec3& vec) : x(static_cast<F>(vec.x)), y(static_cast<F>(vec.y)), z(static_cast<F>(vec.z)) {}

        // Constructor that returns a vec3 with x being vec.x, y being vec.y and z being 0.0
        vec3(const vec2<F>& xy);
        // Constructor that returns a vec3 with x being vec.x, y being vec.y and z being vz
        vec3(const vec2<F>& xy, F vz);

        template<std::floating_point f>
        static vec3<f> zero() { return vec3(static_cast<f>(0.0), static_cast<f>(0.0), static_cast<f>(0.0)); }
        template<std::floating_point f>
        static vec3<f> one() { return vec3(static_cast<f>(1.0), static_cast<f>(1.0), static_cast<f>(1.0)); }
        template<std::floating_point f>
        static vec3<f> right() { return vec3(static_cast<f>(1.0), static_cast<f>(0.0), static_cast<f>(0.0)); }
        template<std::floating_point f>
        static vec3<f> left() { return vec3(static_cast<f>(-1.0), static_cast<f>(0.0), static_cast<f>(0.0)); }
        template<std::floating_point f>
        static vec3<f> up() { return vec3(static_cast<f>(0.0), static_cast<f>(1.0), static_cast<f>(0.0)); }
        template<std::floating_point f>
        static vec3<f> down() { return vec3(static_cast<f>(0.0), static_cast<f>(1.0), static_cast<f>(0.0)); }
        template<std::floating_point f>
        static vec3<f> forward() { return vec3(static_cast<f>(0.0), static_cast<f>(0.0), static_cast<f>(1.0)); }
        template<std::floating_point f>
        static vec3<f> backward() { return vec3(static_cast<f>(0.0), static_cast<f>(0.0), static_cast<f>(-1.0)); }

        template<std::floating_point type>
        type X() const { return static_cast<type>(x); }
        template<std::floating_point type>
        type Y() const { return static_cast<type>(y); }
        template<std::floating_point type>
        type Z() const { return static_cast<type>(z); }

        template<std::floating_point type>
        vec2<type> XX() const { type f = static_cast<type>(x); return vec2<type>(f, f); }
        template<std::floating_point type>
        vec2<type> YY() const { type f = static_cast<type>(y); return vec2(f, f); }
        template<std::floating_point type>
        vec2<type> ZZ() const { type f = static_cast<type>(z); return vec2(f, f); }
        template<std::floating_point type>
        vec2<type> XY() const { return vec2(static_cast<type>(x), static_cast<type>(y)); }
        template<std::floating_point type>
        vec2<type> XZ() const { return vec2(static_cast<type>(x), static_cast<type>(z)); }
        template<std::floating_point type>
        vec2<type> YX() const { return vec2(static_cast<type>(y), static_cast<type>(x)); }
        template<std::floating_point type>
        vec2<type> YZ() const { return vec2(static_cast<type>(y), static_cast<type>(z)); }
        template<std::floating_point type>
        vec2<type> ZX() const { return vec2(static_cast<type>(z), static_cast<type>(x)); }
        template<std::floating_point type>
        vec2<type> ZY() const { return vec2(static_cast<type>(z), static_cast<type>(x)); } 

        template<std::floating_point type>
        vec3<type> XXX() const 
        { 
            type f1 = static_cast<type>(x);
            
            return vec3<type>(f1, f1, f1); 
        }
        template<std::floating_point type>
        vec3<type> YYY() const 
        { 
            type f2 = static_cast<type>(y);
            
            return vec3<type>(f2, f2, f2); 
        }
        template<std::floating_point type>
        vec3<type> ZZZ() const 
        { 
            type f3 = static_cast<type>(z);
            
            return vec3<type>(f3, f3, f3); 
        }
        template<std::floating_point type>
        vec3<type> XYZ() const 
        { 
            type f1 = static_cast<type>(x);
            type f2 = static_cast<type>(y);
            type f3 = static_cast<type>(z);
            
            return vec3<type>(f1, f2, f3); 
        }
        template<std::floating_point type>
        vec3<type> ZYX() const 
        { 
            type f1 = static_cast<type>(x);
            type f2 = static_cast<type>(y);
            type f3 = static_cast<type>(z);
            
            return vec3<type>(f3, f2, f1); 
        }


        // Returns a float pointer of the vector's value at the specified index (x -> 0, y -> 1, z -> 2)
        // The specified index is clamped between 0 and 2
        F* operator[](int index) 
        {
            index = clamp(index, 0, 2);

            return &data[index];
        }

        template<Number N>
        N length() const
        {
            return static_cast<N>(std::sqrtf( (x * x) + (y * y) + (z * z) ));
        }
        template<Number N>
        N lengthSquared() const 
        {
            return static_cast<N>((x * x) + (y * y) + (z * z));
        }

        template<Number N>
        N dotProduct(const vec3& other) const 
        {
            return static_cast<N>((x * other.x) + (y * other.y) + (z * other.y));
        }
        vec3<F> crossProduct(const vec3<F>& other) const 
        {
            // Le pruduit vectoriel de u par v est 
            // u x v = [ uY x vZ - uZ x vY, -(uX x vZ - uZ x vX), uX x vY - uY x vX ]

            F x = y * other.z - z * other.y;
            F y = -(x * other.z - z * other.x);
            F z = x * other.y - y * other.x;

            return vec3(x, y, z);
        }

        template<Number N>
        N distance(const vec3& other) const
        {
            return static_cast<N>(std::sqrtf( (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) +(other.z - z) * (other.z - z) ));
        }
        template<Number N>
        N distanceSquared(const vec3& other) const
        {
            return static_cast<N>((other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) + (other.z - z) * (other.z - z));
        }

        template<Number N>
        static N length(const vec3& vec) 
        {
            return static_cast<N>(std::sqrtf( (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) ));
        }
        template<Number N>
        static N lengthSquared(const vec3 vec)  
        {
            return static_cast<N>((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
        }

        template<Number N>
        static N dotProduct(const vec3& vec1, const vec3& vec2)  
        {
            return static_cast<N>((vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.y));
        }

        static vec3 crossProduct(const vec3& a, const vec3& b)
        {
            // Le pruduit vectoriel de u par v est 
            // u x v = [ uY x vZ - uZ x vY, -(uX x vZ - uZ x vX), uX x vY - uY x vX ]

            F x = a.y * b.z - a.z * b.y;
            F y = -(a.x * b.z - a.z * b.x);
            F z = a.x * b.y - a.y * b.x;

            return vec3(x, y, z);
        }

        template<Number N>
        static N distance(const vec3& vec1, const vec3& vec2) 
        {
            return static_cast<N>(std::sqrtf( (vec2.x - vec1.x) * (vec2.x - vec1.x) + 
                                              (vec2.y - vec1.y) * (vec2.y - vec1.y) +
                                              (vec2.z - vec1.z) * (vec2.z - vec1.z) ));
        }
        template<Number N>
        static N distanceSquared(const vec3& vec1, const vec3& vec2) 
        {
            return static_cast<N>((vec2.x - vec1.x) * (vec2.x - vec1.x) + 
                                  (vec2.y - vec1.y) * (vec2.y - vec1.y) +
                                  (vec2.z - vec1.z) * (vec2.z - vec1.z));
        }

        // well ..., I don't know what this does (thanks Unity), and I'm not motivated tonigth, I'll fix it tomorrow :)

        static vec3 moveTowards(const vec3& current, const vec3& target, F maxDistance)
        {
            F x = target.x - current.x;
            F y = target.y - current.y;
            F z = target.z - current.z;

            F distanceSqr = x * x + y * y + z * z;

            if (distanceSqr == static_cast<F>(0.0) || (maxDistance >= static_cast<F>(0.0) && distanceSqr <= maxDistance * maxDistance))
            {
                return target;
            }

            F distance = static_cast<F>(std::sqrtf(distanceSqr));

            return vec3(current.x + x / distance * maxDistance,
                        current.y + y / distance * maxDistance,
                        current.z + z / distance * maxDistance);

        }


        vec3& normalized()
        {
            double l = this->length<double>();
            if (l > 0.0) 
            {
                F inverseLength = static_cast<F>(1.0 / l);

                x *= inverseLength;
                y *= inverseLength;
                z *= inverseLength;
            }

            return *this;
        }

        template<std::floating_point type>
        vec3<type> getUnitVector() const
        {
            vec3 copy = *this;
            copy = copy.normalized();

            vec3<type> vec = vec3<type>(static_cast<type>(copy.x), 
                                        static_cast<type>(copy.y),
                                        static_cast<type>(copy.z));

            return vec;
        }

        template<std::floating_point f>
        static vec3 lerp(const vec3& start, const vec3& end, f t)
        {
            t = clamp01(t);

            return vec3(start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t, start.y + (end.y - start.y) * t);
        }
        template<std::floating_point f>
        static vec3 lerpUnclamped(const vec3& start, const vec3& end, f t)
        {
            return vec3(start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t, start.y + (end.y - start.y) * t);
        }


        vec3& operator+=(const vec3& other) 
        { 
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            
            return *this; 
        }
        vec3& operator-=(const vec3& other) 
        { 
            this->x -= other.x;
            this->y -= other.y;
            this->z -= other.z;
            
            return *this; 
        }
        vec3& operator*=(F scalar)
        {
            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;

            return *this;
        }
        vec3& operator/=(F scalar)
        {
            if (scalar == static_cast<F>(0.0)) return *this;

            scalar = static_cast<F>(1.0) / scalar;

            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;

            return *this;
        }

    };

    template<std::floating_point F>
    inline vec3<F> operator+(const vec3<F>& a, const vec3<F>& b)
    {
        return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
    }
    template<std::floating_point F>
    inline vec3<F> operator-(const vec3<F>& a, const vec3<F>& b)
    {
        return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
    }
    template<std::floating_point F>
    inline vec3<F> operator*(const vec3<F>& vec, F scalar)
    {
        return vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }
    template<std::floating_point F>
    inline vec3<F> operator*(F scalar, const vec3<F>& vec)
    {
        return vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }
    template<std::floating_point F>
    inline vec3<F> operator/(const vec3<F>& vec, F scalar)
    {
        if (scalar == static_cast<F>(0.0)) return vec;

        scalar = static_cast<F>(1.0) / scalar;

        return vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }

    template<std::floating_point F>
    inline bool operator==(const vec3<F>& a, const vec3<F>& b)
    {
        return static_cast<F>(std::abs(a.x - b.x)) < math::epsilon<F>() && 
               static_cast<F>(std::abs(a.y - b.y)) < math::epsilon<F>() &&
               static_cast<F>(std::abs(a.z - b.z)) < math::epsilon<F>();
    }

    template<std::floating_point F>
    inline bool operator!=(const vec3<F>& a, const vec3<F>& b)
    {
        return !(a == b);
    }
}
