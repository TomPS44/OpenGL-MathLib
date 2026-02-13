#include <concepts>
#include <cmath>
#include "Vector3.hpp"

namespace math
{

    #pragma region Constructors

    template<std::floating_point F>
    inline vec3<F>::vec3() 
    {
        x = static_cast<F>(0.0);
        y = static_cast<F>(0.0);
        z = static_cast<F>(0.0);
    }

    template<std::floating_point F>
    inline vec3<F>::vec3(F vx, F vy)
    {
        x = vx;
        y = vy;
        z = static_cast<F>(0.0);
    }

    template<std::floating_point F>
    inline vec3<F>::vec3(F vx, F vy, F vz)
    {
        x = vx;
        y = vy;
        z = vz;
    }

    template<std::floating_point F>
    inline vec3<F>::vec3(const vec3<F>& vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }


    template<std::floating_point F>
    inline vec3<F>::vec3(const vec2<F>& vec)
    {
        x = vec.x;
        y = vec.y;
        z = static_cast<F>(0.0);
    }

    template<std::floating_point F>
    inline vec3<F>::vec3(const vec2<F>& vec, F vz)
    {
        x = vec.x;
        y = vec.y;
        z = vz;
    }

    
    
    #pragma endregion Constructors

    #pragma region StaticConstructors

    template<std::floating_point F>
    inline vec3<F> vec3<F>::zero()
    {
        F f = static_cast<F>(0.0);
        return vec3(f, f, f);
    }
    template<std::floating_point F>
    inline vec3<F> vec3<F>::one()
    {
        F f = static_cast<F>(1.0);
        return vec3(f, f, f);
    }
    template<std::floating_point F>
    inline vec3<F> vec3<F>::up()
    {
        F f = static_cast<F>(0.0);
        return vec3(f, static_cast<F>(1.0), f);
    }
    template<std::floating_point F>
    inline vec3<F> vec3<F>::down()
    {
        F f = static_cast<F>(0.0);
        return vec3(f, static_cast<F>(-1.0), f);
    }
    template<std::floating_point F>
    inline vec3<F> vec3<F>::left()
    {
        F f = static_cast<F>(0.0);
        return vec3(static_cast<F>(-1.0), f, f);
    }
    template<std::floating_point F>
    inline vec3<F> vec3<F>::right()
    {
        F f = static_cast<F>(0.0);
        return vec3(static_cast<F>(1.0), f, f);
    }
    template<std::floating_point F>
    inline vec3<F> vec3<F>::forward()
    {
        F f = static_cast<F>(0.0);
        return vec3(f, f, static_cast<F>(1.0));
    }
    template<std::floating_point F>
    inline vec3<F> vec3<F>::backward()
    {
        F f = static_cast<F>(0.0);
        return vec3(f, f, static_cast<F>(-1.0));
    }

    #pragma endregion StaticConstructors

    #pragma region Casting

    template<std::floating_point F>
    template<std::floating_point f>
    inline f vec3<F>::X() const
    {
        return static_cast<f>(x);
    }
    template<std::floating_point F>
    template<std::floating_point f>
    inline f vec3<F>::Y() const
    {
        return static_cast<f>(y);
    }
    template<std::floating_point F>
    template<std::floating_point f>
    inline f vec3<F>::Z() const
    {
        return static_cast<f>(z);
    }


    template <std::floating_point F>
    template <std::floating_point f>
    inline vec2<f> vec3<F>::XX() const
    {
        f f1 = static_cast<f>(x);

        return vec2<f>(f1, f1);
    }

    template <std::floating_point F>
    template <std::floating_point f>
    inline vec2<f> vec3<F>::YY() const
    {
        f f1 = static_cast<f>(y);

        return vec2<f>(f1, f1);
    }

    template <std::floating_point F>
    template <std::floating_point f>
    inline vec2<f> vec3<F>::ZZ() const
    {
        f f1 = static_cast<f>(z);

        return vec2<f>(f1, f1);
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec2<f> vec3<F>::XY() const
    {
        return vec2<f>(x, y);
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec2<f> vec3<F>::XZ() const
    {
        return vec2<f>(x, z);
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec2<f> vec3<F>::YX() const
    {
        return vec2<f>(y, x);
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec2<f> vec3<F>::YZ() const
    {
        return vec2<f>(y, z);
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec2<f> vec3<F>::ZX() const
    {
        return vec2<f>(z, x);
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec2<f> vec3<F>::ZY() const
    {
        return vec2<f>(z, y);
    }


    template<std::floating_point F>
    template<std::floating_point f>
    inline vec3<f> vec3<F>::XYZ() const
    {
        return vec3<f>(static_cast<f>(x), static_cast<f>(y), static_cast<f>(z));
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec3<f> vec3<F>::ZYX() const
    {
        return vec3<f>(static_cast<f>(z), static_cast<f>(y), static_cast<f>(x));
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec3<f> vec3<F>::XXX() const
    {
        return vec3<f>(static_cast<f>(x), static_cast<f>(x), static_cast<f>(x));
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec3<f> vec3<F>::YYY() const
    {
        return vec3<f>(static_cast<f>(y), static_cast<f>(y), static_cast<f>(y));
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec3<f> vec3<F>::ZZZ() const
    {
        return vec3<f>(static_cast<f>(z), static_cast<f>(z), static_cast<f>(z));
    }

    

    #pragma endregion Casting

    #pragma region Normalizing

    template<std::floating_point F>
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

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec3<f> vec3<F>::getUnitVector() const
    {
        vec3 copy = *this;
        copy = copy.normalized();

        vec3<f> vec = vec3<f>(static_cast<f>(copy.x), 
                              static_cast<f>(copy.y),
                              static_cast<f>(copy.z));

        return vec;
    }

    #pragma endregion Normalizing

    #pragma region MemberMethods

    template<std::floating_point F>
    const F* vec3<F>::valuePtr() const
    {
        return &data[0];
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec3<F>::length() const
    {
        return static_cast<N>(std::sqrtf( (x * x) + (y * y) + (z * z) ));
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec3<F>::lengthSquared() const
    {
        return static_cast<N>( (x * x) + (y * y) + (z * z) );
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec3<F>::distance(const vec3<F>& other) const
    {
        return static_cast<N>(std::sqrtf( (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) +(other.z - z) * (other.z - z) ));
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec3<F>::distanceSquared(const vec3<F>& other) const
    {
        return static_cast<N>(std::sqrtf( (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) +(other.z - z) * (other.z - z) ));
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec3<F>::dotProduct(const vec3<F>& other) const
    {
        return static_cast<N>( (x * other.x) + (y * other.y) + (z * other.y) );
    }

    template<std::floating_point F>
    inline vec3<F> vec3<F>::crossProduct(const vec3<F>& other) const
    {
        F x = y * other.z - z * other.y;
        F y = -(x * other.z - z * other.x);
        F z = x * other.y - y * other.x;

        return vec3(x, y, z);
    }

    #pragma endregion MemberMethods

    #pragma region StaticMethods

    template<std::floating_point F>
    template<Number N>
    inline N vec3<F>::length(const vec3<F>& vec) 
    {
        return static_cast<N>(std::sqrtf( (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) ));
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec3<F>::lengthSquared(const vec3<F>& vec) 
    {
        return static_cast<N>( (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) );
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec3<F>::distance(const vec3<F>& a, const vec3<F>& b) 
    {
        return static_cast<N>(std::sqrtf( (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) +(b.z - a.z) * (b.z - a.z) ));
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec3<F>::distanceSquared(const vec3<F>& a, const vec3<F>& b) 
    {
        return static_cast<N>(std::sqrtf( (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) +(b.z - a.z) * (b.z - a.z) ));
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec3<F>::dotProduct(const vec3<F>& a, const vec3<F>& b) 
    {
        return static_cast<N>( (a.x * b.x) + (a.y * b.y) + (a.z * b.y) );
    }

    template<std::floating_point F>
    inline vec3<F> vec3<F>::crossProduct(const vec3<F>& a, const vec3<F>& b) 
    {
        F x = a.y * b.z - a.z * b.y;
        F y = -(a.x * b.z - a.z * b.x);
        F z = a.x * b.y - a.y * b.x;

        return vec3(x, y, z);
    }


    template<std::floating_point F>
    template<std::floating_point f>
    inline vec3<F> vec3<F>::lerp(const vec3<F>& start, const vec3<F>& end, f t)
    {
        t = clamp01(t);
        return vec3(start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t, start.y + (end.y - start.y) * t);
    }
    template<std::floating_point F>
    template<std::floating_point f>
    inline vec3<F> vec3<F>::lerpUnclamped(const vec3<F>& start, const vec3<F>& end, f t)
    {
        return vec3(start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t, start.y + (end.y - start.y) * t);
    }

    #pragma endregion StaticMethods

    #pragma region ReferenceOperators

    template<std::floating_point F>
    vec3<F>& vec3<F>::operator+=(const vec3<F>& other)
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }

    template<std::floating_point F>
    vec3<F>& vec3<F>::operator-=(const vec3<F>& other)
    {
        this->x -= other.x;
        this->y -= other.y;

        return *this;
    }

    template<std::floating_point F>
    vec3<F>& vec3<F>::operator*=(F scalar)
    {
        this->x *= scalar;
        this->y *= scalar;

        return *this;
    }

    template<std::floating_point F>
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

    #pragma endregion ArithmeticOperators
    
}