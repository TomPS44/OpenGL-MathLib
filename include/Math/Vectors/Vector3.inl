#include <concepts>
#include <cmath>

#include "Math\MathInternal.hpp"

namespace math
{

    #pragma region Constructors

    template<FloatingNumber F>
    inline vec3<F>::vec3() 
    {
        x = static_cast<F>(0.0);
        y = static_cast<F>(0.0);
        z = static_cast<F>(0.0);
    }

    template<FloatingNumber F>
    inline vec3<F>::vec3(F vx, F vy)
    {
        x = vx;
        y = vy;
        z = static_cast<F>(0.0);
    }

    template<FloatingNumber F>
    inline vec3<F>::vec3(F vx, F vy, F vz)
    {
        x = vx;
        y = vy;
        z = vz;
    }

    template<FloatingNumber F>
    inline vec3<F>::vec3(const vec3<F>& vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }


    template<FloatingNumber F>
    inline vec3<F>::vec3(const vec2<F>& vec)
    {
        x = vec.x;
        y = vec.y;
        z = static_cast<F>(0.0);
    }

    template<FloatingNumber F>
    inline vec3<F>::vec3(const vec2<F>& vec, F vz)
    {
        x = vec.x;
        y = vec.y;
        z = vz;
    }

    
    
    #pragma endregion Constructors

    #pragma region StaticConstructors

    template<FloatingNumber F>
    inline vec3<F> vec3<F>::zero()
    {
        F f = static_cast<F>(0.0);
        return vec3(f, f, f);
    }
    template<FloatingNumber F>
    inline vec3<F> vec3<F>::one()
    {
        F f = static_cast<F>(1.0);
        return vec3(f, f, f);
    }
    template<FloatingNumber F>
    inline vec3<F> vec3<F>::up()
    {
        F f = static_cast<F>(0.0);
        return vec3(f, static_cast<F>(1.0), f);
    }
    template<FloatingNumber F>
    inline vec3<F> vec3<F>::down()
    {
        F f = static_cast<F>(0.0);
        return vec3(f, static_cast<F>(-1.0), f);
    }
    template<FloatingNumber F>
    inline vec3<F> vec3<F>::left()
    {
        F f = static_cast<F>(0.0);
        return vec3(static_cast<F>(-1.0), f, f);
    }
    template<FloatingNumber F>
    inline vec3<F> vec3<F>::right()
    {
        F f = static_cast<F>(0.0);
        return vec3(static_cast<F>(1.0), f, f);
    }
    template<FloatingNumber F>
    inline vec3<F> vec3<F>::forward()
    {
        F f = static_cast<F>(0.0);
        return vec3(f, f, static_cast<F>(1.0));
    }
    template<FloatingNumber F>
    inline vec3<F> vec3<F>::backward()
    {
        F f = static_cast<F>(0.0);
        return vec3(f, f, static_cast<F>(-1.0));
    }

    #pragma endregion StaticConstructors

    #pragma region Casting

    template <FloatingNumber F>
    inline vec2<F> vec3<F>::XX() const
    {
        return vec2<F>(x, x);
    }

    template <FloatingNumber F>
    inline vec2<F> vec3<F>::YY() const
    {
        return vec2<F>(y, y);
    }

    template <FloatingNumber F>
    inline vec2<F> vec3<F>::ZZ() const
    {
        return vec2<F>(z, z);
    }

    template<FloatingNumber F>
    inline vec2<F> vec3<F>::XY() const
    {
        return vec2<F>(x, y);
    }

    template<FloatingNumber F>
    inline vec2<F> vec3<F>::XZ() const
    {
        return vec2<F>(x, z);
    }

    template<FloatingNumber F>
    inline vec2<F> vec3<F>::YX() const
    {
        return vec2<F>(y, x);
    }

    template<FloatingNumber F>
    inline vec2<F> vec3<F>::YZ() const
    {
        return vec2<F>(y, z);
    }

    template<FloatingNumber F>
    inline vec2<F> vec3<F>::ZX() const
    {
        return vec2<F>(z, x);
    }

    template<FloatingNumber F>
    inline vec2<F> vec3<F>::ZY() const
    {
        return vec2<F>(z, y);
    }


    template<FloatingNumber F>
    template<FloatingNumber f>
    inline vec3<f> vec3<F>::as() const
    {
        return vec3<f>(static_cast<f>(x), static_cast<f>(y), static_cast<f>(z));
    }

    template<FloatingNumber F>
    inline vec3<F> vec3<F>::ZYX() const
    {
        return vec3<F>(z, y, x);
    }

    template<FloatingNumber F>
    inline vec3<F> vec3<F>::XXX() const
    {
        return vec3<F>(x, x, x);
    }

    template<FloatingNumber F>
    inline vec3<F> vec3<F>::YYY() const
    {
        return vec3<F>(y, y, y);
    }

    template<FloatingNumber F>
    inline vec3<F> vec3<F>::ZZZ() const
    {
        return vec3<F>(z, z, z);
    }

    

    #pragma endregion Casting

    #pragma region Normalizing

    template<FloatingNumber F>
    inline vec3<F>& vec3<F>::normalized()
    {
        F l = this->length<F>();

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
    inline vec3<F> vec3<F>::getUnitVector() const
    {
        vec3 copy = *this;

        return copy.normalized();
    }

    #pragma endregion Normalizing

    #pragma region MemberMethods

    template<FloatingNumber F>
    const F* vec3<F>::valuePtr() const
    {
        return &data[0];
    }

    template<FloatingNumber F>
    template<Number N>
    inline N vec3<F>::length() const
    {
        return static_cast<N>(std::sqrtf( (x * x) + (y * y) + (z * z) ));
    }

    template<FloatingNumber F>
    template<Number N>
    inline N vec3<F>::lengthSquared() const
    {
        return static_cast<N>( (x * x) + (y * y) + (z * z) );
    }

    template<FloatingNumber F>
    template<Number N>
    inline N vec3<F>::distance(const vec3<F>& other) const
    {
        return static_cast<N>(std::sqrtf( (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) +(other.z - z) * (other.z - z) ));
    }

    template<FloatingNumber F>
    template<Number N>
    inline N vec3<F>::distanceSquared(const vec3<F>& other) const
    {
        return static_cast<N>(std::sqrtf( (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) +(other.z - z) * (other.z - z) ));
    }

    template<FloatingNumber F>
    template<Number N>
    inline N vec3<F>::dotProduct(const vec3<F>& other) const
    {
        return static_cast<N>( (x * other.x) + (y * other.y) + (z * other.z) );
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

    #pragma endregion MemberMethods

    #pragma region StaticMethods

    template<FloatingNumber F>
    template<Number N>
    inline N vec3<F>::length(const vec3<F>& vec) 
    {
        return static_cast<N>(std::sqrtf( (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) ));
    }

    template<FloatingNumber F>
    template<Number N>
    inline N vec3<F>::lengthSquared(const vec3<F>& vec) 
    {
        return static_cast<N>( (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) );
    }

    template<FloatingNumber F>
    template<Number N>
    inline N vec3<F>::distance(const vec3<F>& a, const vec3<F>& b) 
    {
        return static_cast<N>(std::sqrtf( (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) +(b.z - a.z) * (b.z - a.z) ));
    }

    template<FloatingNumber F>
    template<Number N>
    inline N vec3<F>::distanceSquared(const vec3<F>& a, const vec3<F>& b) 
    {
        return static_cast<N>(std::sqrtf( (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) +(b.z - a.z) * (b.z - a.z) ));
    }

    template<FloatingNumber F>
    template<Number N>
    inline N vec3<F>::dotProduct(const vec3<F>& a, const vec3<F>& b) 
    {
        return static_cast<N>( (a.x * b.x) + (a.y * b.y) + (a.z * b.z) );
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
    template<FloatingNumber f>
    inline vec3<F> vec3<F>::lerp(const vec3<F>& start, const vec3<F>& end, f t)
    {
        t = clamp01(t);
        return vec3(start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t, start.z + (end.z - start.z) * t);
    }
    template<FloatingNumber F>
    template<FloatingNumber f>
    inline vec3<F> vec3<F>::lerpUnclamped(const vec3<F>& start, const vec3<F>& end, f t)
    {
        return vec3(start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t, start.z + (end.z - start.z) * t);
    }

    #pragma endregion StaticMethods

    #pragma region ReferenceOperators

    template<FloatingNumber F>
    vec3<F>& vec3<F>::operator+=(const vec3<F>& other)
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }

    template<FloatingNumber F>
    vec3<F>& vec3<F>::operator-=(const vec3<F>& other)
    {
        this->x -= other.x;
        this->y -= other.y;

        return *this;
    }

    template<FloatingNumber F>
    vec3<F>& vec3<F>::operator*=(F scalar)
    {
        this->x *= scalar;
        this->y *= scalar;

        return *this;
    }

    template<FloatingNumber F>
    vec3<F>& vec3<F>::operator/=(F scalar)
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
    inline vec3<F> operator-(const vec3<F>& a, const vec3<F>& b)
    {
        return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
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
        return static_cast<F>(std::abs(a.x - b.x)) < math::epsilon<F>() && 
               static_cast<F>(std::abs(a.y - b.y)) < math::epsilon<F>() &&
               static_cast<F>(std::abs(a.z - b.z)) < math::epsilon<F>();
    }

    template<FloatingNumber F>
    inline bool operator!=(const vec3<F>& a, const vec3<F>& b)
    {
        return !(a == b);
    }

    #pragma endregion ArithmeticOperators
    
}