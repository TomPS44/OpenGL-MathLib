#include <concepts>
#include <cmath>

#include <algorithm>

#include "Math\MathInternal.hpp"

#include <immintrin.h>

namespace glMath
{

    #pragma region Constructors

    template<FloatingNumber F>
    inline vec3<F>::vec3() 
        : x(static_cast<F>(0.0)), y(static_cast<F>(0.0)), z(static_cast<F>(0.0))
    {}

    template<FloatingNumber F>
    inline vec3<F>::vec3(F scalar)
        : x(scalar), y(scalar), z(scalar) 
    {}

    template<FloatingNumber F>
    inline vec3<F>::vec3(F vx, F vy)
        : x(vx), y(vy), z(static_cast<F>(0.0))
    {}

    template<FloatingNumber F>
    inline vec3<F>::vec3(F vx, F vy, F vz)
        : x(vx), y(vy), z(vz)
    {}

    template<FloatingNumber F>
    inline vec3<F>::vec3(const vec3<F>& vec)
        : x(vec.x), y(vec.y), z(vec.z)
    {}


    template<FloatingNumber F>
    inline vec3<F>::vec3(const vec2<F>& vec)
        : x(vec.x), y(vec.y), z(static_cast<F>(0.0))
    {}

    template<FloatingNumber F>
    inline vec3<F>::vec3(const vec2<F>& vec, F vz)
        : x(vec.x), y(vec.y), z(vz)
    {}
    
    #pragma endregion Constructors

    #pragma region StaticConstructors

    template<FloatingNumber F>
    inline vec3<F> vec3<F>::fromQuat(const quat<F>& angle)
    {
        vec3<F> angles;

        F qw = angle.w;
        F qx = angle.x;
        F qy = angle.y;
        F qz = angle.z;

        F f1 = static_cast<F>(1.0);
        F f2 = static_cast<F>(2.0);

        F sinX = f2 * (qw * qx - qy * qz);
        
        if (std::abs(sinX) >= static_cast<F>(0.99999)) 
        {
            angles.x = std::copysign(glMath::pi<F>() * static_cast<F>(0.5), sinX);
            angles.y = f2 * std::atan2(qy, qw);
            angles.z = static_cast<F>(0.0);
        } 
        else   
        {
            angles.x = std::asin(sinX);
            angles.y = std::atan2(f2 * (qw * qy + qz * qx), f1 - f2 * (qx * qx + qy * qy));
            angles.z = std::atan2(f2 * (qw * qz + qx * qy), f1 - f2 * (qz * qz + qx * qx));
        }

        angles.x *= glMath::radToDeg<F>();
        angles.y *= glMath::radToDeg<F>();
        angles.z *= glMath::radToDeg<F>();

        return angles;
    }

    #pragma endregion StaticConstructors

    #pragma region Casting


    template<FloatingNumber F>
    template<FloatingNumber f>
    inline vec3<f> vec3<F>::as() const
    {
        std::numeric_limits<f> limit = std::numeric_limits<f>();
        f minLimit = limit.lowest();
        f maxLimit = limit.max();

        return vec3<f>(
            std::clamp(static_cast<f>(x), minLimit, maxLimit), 
            std::clamp(static_cast<f>(y), minLimit, maxLimit), 
            std::clamp(static_cast<f>(z), minLimit, maxLimit)
        );
    }    

    #pragma endregion Casting

    #pragma region Normalizing

    template<FloatingNumber F>
    inline vec3<F>& vec3<F>::normalize()
    {
        F l = this->length();

        if (l > static_cast<F>(0.0))
        {
            F inverseLength = static_cast<F>(1.0 / l);

            x *= inverseLength;
            y *= inverseLength;
            z *= inverseLength;
        }

        return *this;
    }

    template<FloatingNumber F>
    inline vec3<F> vec3<F>::getNormalizedVec() const
    {
        vec3 copy = *this;

        return copy.normalize();
    }

    #pragma endregion Normalizing

    #pragma region MemberMethods

    template<FloatingNumber F>
    const F* vec3<F>::valuePtr() const
    {
        return &data[0];
    }

    template<FloatingNumber F>
    inline F vec3<F>::length() const
    {
        return std::sqrt( (x * x) + (y * y) + (z * z) );
    }

    template<FloatingNumber F>
    inline F vec3<F>::lengthSquared() const
    {
        return  (x * x) + (y * y) + (z * z);
    }

    template<FloatingNumber F>
    inline F vec3<F>::distance(const vec3<F>& other) const
    {
        return std::sqrt( (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) +(other.z - z) * (other.z - z) );
    }

    template<FloatingNumber F>
    inline F vec3<F>::distanceSquared(const vec3<F>& other) const
    {
        return std::sqrt( (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) +(other.z - z) * (other.z - z) );
    }

    template<FloatingNumber F>
    inline F vec3<F>::dotProduct(const vec3<F>& other) const
    {
        return  (x * other.x) + (y * other.y) + (z * other.z);
    }

    template<FloatingNumber F>
    inline vec3<F> vec3<F>::crossProduct(const vec3<F>& other) const
    {
        return vec3<F>(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }


    template<FloatingNumber F>
    inline vec3<F> vec3<F>::min(const vec3<F>& other) const
    {
        return vec3<F>(glMath::min(x, other.x), glMath::min(y, other.y), glMath::min(z, other.z));
    }
    template<FloatingNumber F>
    inline vec3<F> vec3<F>::max(const vec3<F>& other) const
    {
        return vec3<F>(glMath::max(x, other.x), glMath::max(y, other.y), glMath::max(z, other.z));
    }

    #pragma endregion MemberMethods

    #pragma region StaticMethods

    template<FloatingNumber F>
    inline vec3<F> vec3<F>::normalized(const vec3<F>& vec)
    {
        return vec.getNormalizedVec();
    }

    template<FloatingNumber F>
    inline F vec3<F>::length(const vec3<F>& vec) 
    {
        return std::sqrt( (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) );
    }

    template<FloatingNumber F>
    inline F vec3<F>::lengthSquared(const vec3<F>& vec) 
    {
        return  (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
    }

    template<FloatingNumber F>
    inline F vec3<F>::distance(const vec3<F>& a, const vec3<F>& b) 
    {
        return std::sqrt( (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) +(b.z - a.z) * (b.z - a.z) );
    }

    template<FloatingNumber F>
    inline F vec3<F>::distanceSquared(const vec3<F>& a, const vec3<F>& b) 
    {
        return std::sqrt( (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) +(b.z - a.z) * (b.z - a.z) );
    }

    template<FloatingNumber F>
    inline F vec3<F>::dotProduct(const vec3<F>& a, const vec3<F>& b) 
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    template<FloatingNumber F>
    inline vec3<F> vec3<F>::crossProduct(const vec3<F>& a, const vec3<F>& b) 
    {
        F vx = a.y * b.z - a.z * b.y;
        F vy = a.z * b.x - a.x * b.z;
        F vz = a.x * b.y - a.y * b.x;

        return vec3(vx, vy, vz);
    }

    
    template<FloatingNumber F>
    inline vec3<F> vec3<F>::min(const vec3<F>& a, const vec3<F>& b)
    {
        return vec3<F>(glMath::min(a.x, b.x), glMath::min(a.y, b.y), glMath::min(a.z, b.z));
    }
    template<FloatingNumber F>
    inline vec3<F> vec3<F>::max(const vec3<F>& a, const vec3<F>& b)
    {
        return vec3<F>(glMath::max(a.x, b.x), glMath::max(a.y, b.y), glMath::max(a.z, b.z));
    }


    template<FloatingNumber F>
    inline vec3<F> vec3<F>::lerp(const vec3<F>& start, const vec3<F>& end, F t)
    {
        t = glMath::clamp01(t);
        return vec3(start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t, start.z + (end.z - start.z) * t);
    }
    template<FloatingNumber F>
    inline vec3<F> vec3<F>::lerpUnclamped(const vec3<F>& start, const vec3<F>& end, F t)
    {
        return vec3(start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t, start.z + (end.z - start.z) * t);
    }

    template<FloatingNumber F>
    inline vec3<F> vec3<F>::slerp(const vec3<F>& start, const vec3<F>& end, F t)
    {
        t = glMath::clamp01(t);
        return vec3<F>::slerpUnclamped(start, end, t);
    }
    template<FloatingNumber F>
    inline vec3<F> vec3<F>::slerpUnclamped(const vec3<F>& start, const vec3<F>& end, F t)
    {
        F dot = vec3<F>::dotProduct(start, end);

        if (dot > static_cast<F>(0.9995))
        {
            return vec3<F>::lerpUnclamped(start, end, t);
        }

        F ang = std::acos(dot);
        F sinAng = std::sin(ang);

        F wA = std::sin((static_cast<F>(1.0) - t) * ang) / sinAng;
        F wB = std::sin(t * ang) / sinAng;

        return (start * wA) + (end * wB);
    }

    #pragma endregion StaticMethods

    #pragma region ReferenceOperators

    template<FloatingNumber F>
    inline vec3<F>& vec3<F>::operator+=(const vec3<F>& other)
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;

        return *this;
    }
    template<FloatingNumber F>
    inline vec3<F>& vec3<F>::operator+=(F scalar)
    {
        this->x += scalar;
        this->y += scalar;
        this->z += scalar;

        return *this;
    }

    template<FloatingNumber F>
    inline vec3<F>& vec3<F>::operator-=(const vec3<F>& other)
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;

        return *this;
    }
    template<FloatingNumber F>
    inline vec3<F>& vec3<F>::operator-=(F scalar)
    {
        this->x -= scalar;
        this->y -= scalar;
        this->z -= scalar;

        return *this;
    }

    template<FloatingNumber F>
    inline vec3<F>& vec3<F>::operator*=(const vec3<F>& other)
    {
        this->x *= other.x;
        this->y *= other.y;
        this->z *= other.z;

        return *this;
    }
    template<FloatingNumber F>
    inline vec3<F>& vec3<F>::operator*=(F scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;

        return *this;
    }

    template<FloatingNumber F>
    inline vec3<F>& vec3<F>::operator/=(F scalar)
    {
        if (scalar != static_cast<F>(0.0))
        {
            scalar = static_cast<F>(1.0) / scalar;

            this->x *= scalar;
            this->y *= scalar;
            this->z *= scalar;
        } 

        return *this;
    }

    #pragma endregion ReferenceOperators

    #pragma region ArithmeticOperators

    template<FloatingNumber F>
    inline vec3<F> operator+(const vec3<F>& a, const vec3<F>& b)
    {
        return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
    }
    template<FloatingNumber F>
    inline vec3<F> operator+(const vec3<F>& a, F scalar)
    {
        return vec3(a.x + scalar, a.y + scalar, a.z + scalar);
    }

    template<FloatingNumber F>
    inline vec3<F> operator-(const vec3<F>& a, const vec3<F>& b)
    {
        return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
    }
    template<FloatingNumber F>
    inline vec3<F> operator-(const vec3<F>& a, F scalar)
    {
        return vec3(a.x - scalar, a.y - scalar, a.z - scalar);
    }


    template <FloatingNumber F>
    inline vec3<F> vec3<F>::operator-() const
    {
        return vec3(-x, -y, -z);
    }


    template<FloatingNumber F>
    inline vec3<F> operator*(const vec3<F>& a, const vec3<F>& b)
    {
        return vec3(a.x * b.x, a.y * b.y, a.z * b.z);
    }
    template<FloatingNumber F>
    inline vec3<F> operator*(const vec3<F>& vec, F scalar)
    {
        return vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }
    template<FloatingNumber F>
    inline vec3<F> operator*(F scalar, const vec3<F>& vec)
    {
        return vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }
    template<FloatingNumber F>
    inline vec3<F> operator/(const vec3<F>& vec, F scalar)
    {
        if (scalar == static_cast<F>(0.0)) return vec;

        scalar = static_cast<F>(1.0) / scalar;

        return vec3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
    }

    template<FloatingNumber F>
    inline bool operator==(const vec3<F>& a, const vec3<F>& b)
    {
        return static_cast<F>(std::abs(a.x - b.x)) < glMath::epsilon<F>() && 
               static_cast<F>(std::abs(a.y - b.y)) < glMath::epsilon<F>() &&
               static_cast<F>(std::abs(a.z - b.z)) < glMath::epsilon<F>();
    }

    template<FloatingNumber F>
    inline bool operator!=(const vec3<F>& a, const vec3<F>& b)
    {
        return !(a == b);
    }

    #pragma endregion ArithmeticOperators
    
}