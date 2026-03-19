#include <concepts>
#include <cmath>

#include <algorithm>

#include "Math\MathInternal.hpp"

#include <immintrin.h>

namespace glMath
{
    #pragma region Constructors

    template<FloatingNumber F>
    inline vec4<F>::vec4()
        :
        x(static_cast<F>(0.0)), 
        y(static_cast<F>(0.0)), 
        z(static_cast<F>(0.0)), 
        w(static_cast<F>(0.0)) 
    {}

    template<FloatingNumber F>
    inline vec4<F>::vec4(F scalar)
        :
        x(scalar), 
        y(scalar), 
        z(scalar), 
        w(scalar) 
    {}

    template<FloatingNumber F>
    inline vec4<F>::vec4(F vx, F vy, F vz, F vw)
        :
        x(vx), 
        y(vy), 
        z(vz), 
        w(vw) 
    {}

    template<FloatingNumber F>
    inline vec4<F>::vec4(const vec4<F>& vec)
        :
        x(vec.x), 
        y(vec.y), 
        z(vec.z), 
        w(vec.w) 
    {}

    template <FloatingNumber F>
    inline vec4<F>::vec4(const vec3<F>& xyz, F vw)
        :
        x(xyz.x),
        y(xyz.y),
        z(xyz.z),
        w(vw)
    {}

    #pragma endregion

    #pragma region Casting

    template<FloatingNumber F>
    template<FloatingNumber f>
    inline vec4<f> vec4<F>::as() const
    {
        std::numeric_limits<f> limit = std::numeric_limits<f>();
        f minLimit = limit.lowest();
        f maxLimit = limit.max();

        return vec4<f>(
            std::clamp(static_cast<f>(x), minLimit, maxLimit), 
            std::clamp(static_cast<f>(y), minLimit, maxLimit), 
            std::clamp(static_cast<f>(z), minLimit, maxLimit),
            std::clamp(static_cast<f>(w), minLimit, maxLimit)
        );
    }


    template<FloatingNumber F>
    inline vec3<F> vec4<F>::toVec3() const
    {
        return vec3<F>(
            x,
            y, 
            z
        );
    }

    template<FloatingNumber F>
    inline vec3<F> vec4<F>::projectToVec3() const
    {
        if (std::abs(w) < glMath::epsilon<F>()) return vec3<F>(x, y, z).normalize();


        F invW = static_cast<F>(1.0) / w;

        return vec3<F>(
            x * invW,
            y * invW, 
            z * invW
        );
    }

    #pragma endregion

    #pragma region Normalizing

    template<FloatingNumber F>
    inline vec4<F>& vec4<F>::normalize()
    {
        F l = this->length();

        if (l > glMath::epsilon<F>()) 
        {
            F invLen = static_cast<F>(1.0) / l;

            x *= invLen;
            y *= invLen;
            z *= invLen;
            w *= invLen;
        }

        return *this;
    }
    template<FloatingNumber F>
    inline vec4<F>& vec4<F>::normalize3()
    {
        F l = this->length3();

        if (l > glMath::epsilon<F>()) 
        {
            F invLen = static_cast<F>(1.0) / l;

            x *= invLen;
            y *= invLen;
            z *= invLen;
        }

        return *this;
    }

    template<FloatingNumber F>
    inline vec4<F> vec4<F>::getNormalizedVec() const
    {
        vec4<F> copy = *this;

        return copy.normalize();
    }
    template<FloatingNumber F>
    inline vec4<F> vec4<F>::getNormalizedVec3() const
    {
        vec4<F> copy = *this;

        return copy.normalize3();
    }

    #pragma endregion

    #pragma region MemberMethods

    template<FloatingNumber F>
    inline const F* vec4<F>::valuePtr() const
    {
        return &data[0];
    }


    template<FloatingNumber F>
    inline F vec4<F>::length() const
    {
        return std::sqrt( (x * x) + (y * y) + (z * z) + (w * w) );
    }
    template<FloatingNumber F>
    inline F vec4<F>::length3() const
    {
        return std::sqrt( (x * x) + (y * y) + (z * z) );
    }

    template<FloatingNumber F>
    inline F vec4<F>::lengthSquared() const
    {
        return (x * x) + (y * y) + (z * z) + (w * w);
    }
    template<FloatingNumber F>
    inline F vec4<F>::lengthSquared3() const
    {
        return (x * x) + (y * y) + (z * z);
    }


    template<FloatingNumber F>
    inline F vec4<F>::dotProduct(const vec4<F>& other) const
    {
        return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
    }

    template<FloatingNumber F>
    inline F vec4<F>::dotProduct3(const vec4<F>& other) const
    {
        return (x * other.x) + (y * other.y) + (z * other.z);
    }


    template<FloatingNumber F>
    inline F vec4<F>::distance(const vec4<F>& other) const
    {
        return std::sqrt( (other.x - x) + (other.y - y) + (other.z - z) + (other.w - w) );
    }
    template<FloatingNumber F>
    inline F vec4<F>::distance3(const vec4<F>& other) const
    {
        return std::sqrt( (other.x - x) + (other.y - y) + (other.z - z) );
    }

    template<FloatingNumber F>
    inline F vec4<F>::distanceSquared(const vec4<F>& other) const
    {
        return (other.x - x) + (other.y - y) + (other.z - z) + (other.w - w);
    }
    template<FloatingNumber F>
    inline F vec4<F>::distanceSquared3(const vec4<F>& other) const
    {
        return (other.x - x) + (other.y - y) + (other.z - z);
    }


    template<FloatingNumber F>
    inline vec4<F> vec4<F>::min(const vec4<F>& other) const
    {
        return vec4<F>(glMath::min(x, other.x), glMath::min(y, other.y), glMath::min(z, other.z), glMath::min(w, other.w));
    }
    template<FloatingNumber F>
    inline vec4<F> vec4<F>::max(const vec4<F>& other) const
    {
        return vec4<F>(glMath::max(x, other.x), glMath::max(y, other.y), glMath::max(z, other.z), glMath::max(w, other.w));
    }

    #pragma endregion

    #pragma region StaticMethods

    template<FloatingNumber F>
    inline vec3<F> vec4<F>::projectToVec3(const vec4<F>& vec)
    {
        return vec.projectToVec3();
    }

    template<FloatingNumber F>
    inline vec4<F> vec4<F>::normalized(const vec4<F>& vec)
    {
        return vec.getNormalizedVec();
    }

    template<FloatingNumber F>
    inline vec4<F> vec4<F>::normalized3(const vec4<F>& vec)
    {
        return vec.getNormalizedVec3();
    }

    template<FloatingNumber F>
    inline F vec4<F>::length(const vec4<F>& vec) 
    {
        return std::sqrt( (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) + (vec.w * vec.w) );
    }
    template<FloatingNumber F>
    inline F vec4<F>::length3(const vec4<F>& vec) 
    {
        return std::sqrt( (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) );
    }

    template<FloatingNumber F>
    inline F vec4<F>::lengthSquared(const vec4<F>& vec) 
    {
        return (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) + (vec.w * vec.w);
    }
    template<FloatingNumber F>
    inline F vec4<F>::lengthSquared3(const vec4<F>& vec) 
    {
        return (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
    }


    template<FloatingNumber F>
    inline F vec4<F>::dotProduct(const vec4<F>& vec1, const vec4<F>& vec2) 
    {
        return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z) + (vec1.w * vec2.w);
    }

    template<FloatingNumber F>
    inline F vec4<F>::dotProduct3(const vec4<F>& vec1, const vec4<F>& vec2) 
    {
        return (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
    }



    template<FloatingNumber F>
    inline F vec4<F>::distance(const vec4<F>& vec1, const vec4<F>& vec2) 
    {
        return std::sqrt( (vec2.x - vec1.x) + (vec2.y - vec1.y) + (vec2.z - vec1.z) + (vec2.w - vec1.w) );
    }
    template<FloatingNumber F>
    inline F vec4<F>::distance3(const vec4<F>& vec1, const vec4<F>& vec2) 
    {
        return std::sqrt( (vec2.x - vec1.x) + (vec2.y - vec1.y) + (vec2.z - vec1.z) );
    }

    template<FloatingNumber F>
    inline F vec4<F>::distanceSquared(const vec4<F>& vec1, const vec4<F>& vec2) 
    {
        return (vec2.x - vec1.x) + (vec2.y - vec1.y) + (vec2.z - vec1.z) + (vec2.w - vec1.w);
    }
    template<FloatingNumber F>
    inline F vec4<F>::distanceSquared3(const vec4<F>& vec1, const vec4<F>& vec2) 
    {
        return (vec2.x - vec1.x) + (vec2.y - vec1.y) + (vec2.z - vec1.z);
    }


    template<FloatingNumber F>
    inline vec4<F> vec4<F>::min(const vec4<F>& a, const vec4<F>& b)
    {
        return vec4<F>(glMath::min(a.x, b.x), glMath::min(a.y, b.y), glMath::min(a.z, b.z), glMath::min(a.w, b.w));
    }
    template<FloatingNumber F>
    inline vec4<F> vec4<F>::max(const vec4<F>& a, const vec4<F>& b)
    {
        return vec4<F>(glMath::max(a.x, b.x), glMath::max(a.y, b.y), glMath::max(a.z, b.z), glMath::max(a.w, b.w));
    }



    template<FloatingNumber F>
    inline vec4<F> vec4<F>::lerp(const vec4<F>& start, const vec4<F>& end, F t)
    {
        t = glMath::clamp01(t);
        return vec4<F>::lerpUnclamped(start, end, t);
    }
    template<FloatingNumber F>
    inline vec4<F> vec4<F>::lerpUnclamped(const vec4<F>& start, const vec4<F>& end, F t)
    {
        return vec4<F>(
            start.x + (end.x - start.x) * t, 
            start.y + (end.y - start.y) * t, 
            start.z + (end.z - start.z) * t, 
            start.w + (end.w - start.x) * t
        );
    }
    

    #pragma endregion

    #pragma region ReferenceOperators

    template <FloatingNumber F>
    inline vec4<F>& vec4<F>::operator+=(const vec4<F>& other)
    {
        *this.x += other.x;
        *this.y += other.y;
        *this.z += other.z;
        *this.w += other.w;
    }
    template <FloatingNumber F>
    inline vec4<F>& vec4<F>::operator+=(F scalar)
    {
        *this.x += scalar;
        *this.y += scalar;
        *this.z += scalar;
        *this.w += scalar;
    }

    template <FloatingNumber F>
    inline vec4<F>& vec4<F>::operator-=(const vec4<F>& other)
    {
        *this.x -= other.x;
        *this.y -= other.y;
        *this.z -= other.z;
        *this.w -= other.w;
    }
    template <FloatingNumber F>
    inline vec4<F>& vec4<F>::operator-=(F scalar)
    {
        *this.x -= scalar;
        *this.y -= scalar;
        *this.z -= scalar;
        *this.w -= scalar;
    }


    template <FloatingNumber F>
    inline vec4<F>& vec4<F>::operator*=(const vec4<F>& other)
    {
        *this.x *= other.x;
        *this.y *= other.y;
        *this.z *= other.z;
        *this.w *= other.w;
    }
    template <FloatingNumber F>
    inline vec4<F>& vec4<F>::operator*=(F scalar)
    {
        *this.x *= scalar;
        *this.y *= scalar;
        *this.z *= scalar;
        *this.w *= scalar;
    }

    template <FloatingNumber F>
    inline vec4<F>& vec4<F>::operator/=(F scalar)
    {
        if (std::abs(scalar) > glMath::epsilon<F>())
        {
            F invScalar = static_cast<F>(1.0) / scalar;

            *this.x *= invScalar;
            *this.y *= invScalar;
            *this.z *= invScalar;
            *this.w *= invScalar;
        }

        return *this;
    }

    #pragma endregion

    #pragma region Operators

    template<FloatingNumber F>
    inline vec4<F> vec4<F>::operator-() const
    {
        return vec4<F>(-x, -y, -z, -w);
    }


    template<FloatingNumber F>
    inline vec4<F> operator+(const vec4<F>& a, const vec4<F>& b) 
    {
        return vec4<F>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
    }
    template<FloatingNumber F>
    inline vec4<F> operator+(const vec4<F>& a, F scalar) 
    {
        return vec4<F>(a.x + scalar, a.y + scalar, a.z + scalar, a.w + scalar);
    }

    template<FloatingNumber F>
    inline vec4<F> operator-(const vec4<F>& a, const vec4<F>& b) 
    {
        return vec4<F>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    }
    template<FloatingNumber F>
    inline vec4<F> operator-(const vec4<F>& a, F scalar) 
    {
        return vec4<F>(a.x - scalar, a.y - scalar, a.z - scalar, a.w - scalar);
    }
    


    template<FloatingNumber F>
    inline vec4<F> operator*(const vec4<F>& a, const vec4<F>& b) 
    {
        return vec4<F>(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
    }
    template<FloatingNumber F>
    inline vec4<F> operator*(const vec4<F>& vec, F scalar) 
    {
        return vec4<F>(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
    }
    template<FloatingNumber F>
    inline vec4<F> operator*(F scalar, const vec4<F>& vec) 
    {
        return vec4<F>(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
    }

    template<FloatingNumber F>
    inline vec4<F> operator/(const vec4<F>& vec, F scalar) 
    {
        if (std::abs(scalar) < glMath::epsilon<F>()) return vec;


        F invScalar = static_cast<F>(1.0) / scalar;

        return vec4<F>(vec.x * invScalar, vec.y * invScalar, vec.z * invScalar, vec.w * invScalar);
    }


    template<FloatingNumber F>
    inline bool operator==(const vec4<F>& a, const vec4<F>& b)
    {
        return static_cast<F>(std::abs(a.x - b.x)) < glMath::epsilon<F>() && 
               static_cast<F>(std::abs(a.y - b.y)) < glMath::epsilon<F>() &&
               static_cast<F>(std::abs(a.z - b.z)) < glMath::epsilon<F>() &&
               static_cast<F>(std::abs(a.w - b.w)) < glMath::epsilon<F>();
    }

    template<FloatingNumber F>
    inline bool operator!=(const vec4<F>& a, const vec4<F>& b)
    {
        return !(a == b);
    }

    #pragma endregion
}