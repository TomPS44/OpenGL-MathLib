#include <concepts>
#include <cmath>

#include <functional>
#include <utility>

#include "Math\MathInternal.hpp"


namespace glMath
{

    #pragma region Constructors

    template<FloatingNumber F>
    inline vec2<F>::vec2()
    {
        x = static_cast<F>(0.0);
        y = static_cast<F>(0.0);
    }

    template <FloatingNumber F>
    inline vec2<F>::vec2(F vx, F vy)
    {
        x = static_cast<F>(vx);
        y = static_cast<F>(vy);
    }

    template<FloatingNumber F>
    inline vec2<F>::vec2(const vec2<F>& vec)
    {
        x = static_cast<F>(vec.x);
        y = static_cast<F>(vec.y);
    }

    #pragma endregion Constructors

    #pragma region StaticConstructors

    template <FloatingNumber F>
    inline vec2<F> vec2<F>::fromAngle(F angleInDeg)
    {
        return vec2(static_cast<F>(std::cos(angleInDeg * glMath::degToRad<F>())), static_cast<F>(std::sin(angleInDeg * glMath::degToRad<F>())));
    }
    
    
    #pragma endregion StaticConstructors

    #pragma region Casting


    template<FloatingNumber F>
    template<FloatingNumber f>
    inline vec2<f> vec2<F>::as() const
    {
        std::numeric_limits<f> limit = std::numeric_limits<f>();
        f minLimit = limit.lowest();
        f maxLimit = limit.max();

        return vec2<f>(
            std::clamp(static_cast<f>(x), minLimit, maxLimit), 
            std::clamp(static_cast<f>(y), minLimit, maxLimit)
        );
    }


    #pragma endregion Casting

    #pragma region Normalizing

    template<FloatingNumber F>
    inline vec2<F>& vec2<F>::normalize()
    {
        F l = this->length();
        
        if (l > static_cast<F>(0.0)) 
        {
            F inverseLength = static_cast<F>(1.0) / l;
            x *= inverseLength; 
            y *= inverseLength;
        }

        return *this;
    }

    template<FloatingNumber F>
    inline vec2<F> vec2<F>::getNormalizedVec() const
    {
        vec2 copy = *this;

        return copy.normalize();
    }

    #pragma endregion Normalizing

    #pragma region MemberMethods


    template<FloatingNumber F>
    template<IntegralNumber i>
    inline iVec2<i> vec2<F>::floorTo() const
    {
        
        std::numeric_limits<i> limit = std::numeric_limits<i>();
        F minLimit = static_cast<F>(limit.lowest());
        F maxLimit = static_cast<F>(limit.max());

        F fx = std::floor(x);
        F fy = std::floor(y);

        return iVec2<i>(
            static_cast<i>(std::clamp(fx, minLimit, maxLimit)),
            static_cast<i>(std::clamp(fy, minLimit, maxLimit))
        );
        
    }


    template<FloatingNumber F>
    inline F vec2<F>::length() const
    {
        return std::sqrt( (x * x) + (y * y) );
    }

    template<FloatingNumber F>
    inline F vec2<F>::lengthSquared() const
    {
        return (x * x) + (y * y);
    }

    template<FloatingNumber F>
    inline F vec2<F>::dotProduct(const vec2& other) const
    {
        return (other.x * x) + (other.x * x) + (other.y * y) + (other.y * y);
    }

    template<FloatingNumber F>
    inline F vec2<F>::distance(const vec2& other) const
    {
        return std::sqrt( (other.x - x) * (other.x - x)  +  (other.y - y) * (other.y - y) );
    }

    template<FloatingNumber F>
    inline F vec2<F>::distanceSquared(const vec2& other) const
    {
        return (other.x - x) * (other.x - x)  +  (other.y - y) * (other.y - y);
    }

    template<FloatingNumber F>
    inline vec2<F> vec2<F>::min(const vec2<F>& other) const
    {
        return vec2<F>(glMath::min(x, other.x), glMath::min(y, other.y));
    }
    template<FloatingNumber F>
    inline vec2<F> vec2<F>::max(const vec2<F>& other) const
    {
        return vec2<F>(glMath::max(x, other.x), glMath::max(y, other.y));
    }

    #pragma endregion MemberMethods

    #pragma region StaticMethods

    template<FloatingNumber F>
    inline F vec2<F>::angleBetween(const vec2<F>& a, const vec2<F>& b)
    {
        F dot = glMath::clamp( vec2<F>::dotProduct(a.getNormalizedVec(), b.getNormalizedVec()), static_cast<F>(-1.0), static_cast<F>(1.0) );

        return std::acos(dot);
    }


    template<FloatingNumber F>
    inline vec2<F> vec2<F>::normalized(const vec2<F>& vec)
    {
        return vec.getNormalizedVec();
    }


    template<FloatingNumber F>
    inline F vec2<F>::length(const vec2<F>& vec) 
    {
        return std::sqrt( (vec.x * vec.x) + (vec.y * vec.y) );
    }

    template<FloatingNumber F>
    inline F vec2<F>::lengthSquared(const vec2& vec) 
    {
        return (vec.x * vec.x) + (vec.y * vec.y);
    }

    template<FloatingNumber F>
    inline F vec2<F>::dotProduct(const vec2& a, const vec2& b)
    {
        return (a.x * b.x) + (a.y * b.y);
    }

    template<FloatingNumber F>
    inline F vec2<F>::distance(const vec2& a, const vec2& b) 
    {
        return std::sqrt( (b.x - a.x) * (b.x - a.x)  +  (b.y - a.y) * (b.y - a.y) );
    }

    template<FloatingNumber F>
    inline F vec2<F>::distanceSquared(const vec2& a, const vec2& b) 
    {
        return (b.x - a.x) * (b.x - a.x)  +  (b.y - a.y) * (b.y - a.y);
    }

    template<FloatingNumber F>
    inline vec2<F> vec2<F>::min(const vec2<F>& a, const vec2<F>& b)
    {
        return vec2<F>(glMath::min(a.x, b.x), glMath::min(a.y, b.y));
    }
    template<FloatingNumber F>
    inline vec2<F> vec2<F>::max(const vec2<F>& a, const vec2<F>& b)
    {
        return vec2<F>(glMath::max(a.x, b.x), glMath::max(a.y, b.y));
    }

    template<FloatingNumber F>
    inline vec2<F> vec2<F>::lerp(const vec2<F>& start, const vec2<F>& end, F t)
    {
        t = clamp01(t);
        return vec2<F>( start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t );
    }

    template<FloatingNumber F>
    inline vec2<F> vec2<F>::lerpUnclamped(const vec2<F>& start, const vec2<F>& end, F t)
    {
        return vec2<F>(start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t);
    }


    template<FloatingNumber F>
    inline vec2<F> vec2<F>::slerp(const vec2<F>& start, const vec2<F>& end, F t)
    {
        t = glMath::clamp01(t);
        return vec2<F>::slerpUnclamped(start, end, t);
    }
    template<FloatingNumber F>
    inline vec2<F> vec2<F>::slerpUnclamped(const vec2<F>& start, const vec2<F>& end, F t)
    {
        F dot = vec2<F>::dotProduct(start, end);

        if (dot > static_cast<F>(0.9995))
        {
            return vec2<F>::lerpUnclamped(start, end, t);
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
    vec2<F>& vec2<F>::operator+=(const vec2<F>& other)
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }

    template<FloatingNumber F>
    vec2<F>& vec2<F>::operator-=(const vec2<F>& other)
    {
        this->x -= other.x;
        this->y -= other.y;

        return *this;
    }

    template<FloatingNumber F>
    vec2<F>& vec2<F>::operator*=(F scalar)
    {
        this->x *= scalar;
        this->y *= scalar;

        return *this;
    }


    template<FloatingNumber F>
    vec2<F>& vec2<F>::operator/=(F scalar)
    {
        if (scalar != static_cast<F>(0.0))
        {
            F invScalar = static_cast<F>(1.0) / scalar;

            this->x *= invScalar;
            this->y *= invScalar;
        }

        return *this;
    }

    template<FloatingNumber F>
    const F* vec2<F>::valuePtr() const
    {
        return &data[0];
    }

    #pragma endregion ReferenceOperators

    #pragma region ArithmeticOperators

    template<FloatingNumber F>
    inline vec2<F> operator+(const vec2<F>& a, const vec2<F>& b)
    {
        return vec2(a.x + b.x, a.y + b.y);
    }
    template<FloatingNumber F>
    inline vec2<F> operator+(const vec2<F>& a, F scalar)
    {
        return vec2(a.x + scalar, a.y + scalar);
    }

    template<FloatingNumber F>
    inline vec2<F> operator-(const vec2<F>& a, const vec2<F>& b)
    {
        return vec2(a.x - b.x, a.y - b.y);
    }
    template<FloatingNumber F>
    inline vec2<F> operator-(const vec2<F>& a, F scalar)
    {
        return vec2(a.x - scalar, a.y - scalar);
    }
    

    template <FloatingNumber F>
    inline vec2<F> vec2<F>::operator-() const
    {
        return vec2(-x, -y);
    }


    template<FloatingNumber F>
    inline vec2<F> operator*(const vec2<F>& a, const vec2<F>& b)
    {
        return vec2(a.x * b.x, a.y * b.y);
    }
    template<FloatingNumber F>
    inline vec2<F> operator*(const vec2<F>& vec, F scalar)
    {
        return vec2(vec.x * scalar, vec.y * scalar);
    }
    template<FloatingNumber F>
    inline vec2<F> operator*(F scalar, const vec2<F>& vec)
    {
        return vec2(vec.x * scalar, vec.y * scalar);
    }

    template<FloatingNumber F>
    inline vec2<F> operator/(const vec2<F>& vec, F scalar)
    {
        if (scalar == static_cast<F>(0.0)) return vec;

        scalar = static_cast<F>(1.0) / scalar;

        return vec2(vec.x / scalar, vec.y / scalar);
    }


    template<FloatingNumber F>
    inline bool operator==(const vec2<F>& a, const vec2<F>& b)
    {
        return static_cast<F>( std::abs(b.x - a.x) ) < glMath::epsilon<F>() &&
               static_cast<F>( std::abs(b.y - a.y) ) < glMath::epsilon<F>();
    }

    template<FloatingNumber F>
    inline bool operator!=(const vec2<F>& a, const vec2<F>& b)
    {
        return !(a == b);
    }

    #pragma endregion ArithmeticOperators

}

