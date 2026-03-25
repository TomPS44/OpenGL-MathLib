#include <concepts>
#include <cmath>

#include <functional>
#include <utility>

#include "Math\MathInternal.hpp"


namespace glMath
{

    #pragma region Constructors

    template<FloatingNumber F>
    inline constexpr vec2<F>::vec2() noexcept
    {
        x = static_cast<F>(0.0);
        y = static_cast<F>(0.0);
    }

    template <FloatingNumber F>
    inline constexpr vec2<F>::vec2(F vx, F vy) noexcept
    {
        x = static_cast<F>(vx);
        y = static_cast<F>(vy);
    }

    template<FloatingNumber F>
    inline constexpr vec2<F>::vec2(const vec2<F>& vec) noexcept
    {
        x = static_cast<F>(vec.x);
        y = static_cast<F>(vec.y);
    }

    #pragma endregion Constructors

    #pragma region StaticConstructors

    template <FloatingNumber F>
    inline vec2<F> vec2<F>::fromAngle(F angleInDeg) noexcept
    {
        F radAng = angleInDeg * glMath::degToRad<F>();

        if constexpr (std::is_same_v<F, float>)
        {
            return vec2<float>(std::cosf(radAng), std::sinf(radAng));
        }
        else
        {
            return vec2<double>(std::cos(radAng), std::sin(radAng));
        }
    }
    
    
    #pragma endregion StaticConstructors

    #pragma region Casting


    template<FloatingNumber F>
    template<FloatingNumber f>
    inline vec2<f> vec2<F>::as() const noexcept
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
    inline vec2<F>& vec2<F>::normalize() noexcept
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
    inline vec2<F> vec2<F>::getNormalizedVec() const noexcept
    {
        vec2 copy = *this;

        return copy.normalize();
    }

    #pragma endregion Normalizing

    #pragma region MemberMethods


    template<FloatingNumber F>
    template<IntegralNumber I>
    inline iVec2<I> vec2<F>::floorTo() const noexcept
    {
        double min = static_cast<double>(std::numeric_limits<I>::min());
        double max = static_cast<double>(std::numeric_limits<I>::max());

        if constexpr (std::is_same_v<F, float>)
        {
            vec2<double> preciseVec = vec2<double>(static_cast<double>(x), static_cast<double>(y));

            return iVec2<I>(
                static_cast<I>(std::clamp(std::floor(preciseVec.x), min, max)),
                static_cast<I>(std::clamp(std::floor(preciseVec.y), min, max))
            );
        }
        else
        {
            return iVec2<I>(
                static_cast<I>(std::clamp(std::floor(x), min, max)),
                static_cast<I>(std::clamp(std::floor(y), min, max))
            );
        }
    }

    template<FloatingNumber F>
    template<IntegralNumber I>
    inline iVec2<I> vec2<F>::ceilTo() const noexcept
    {
        double min = static_cast<double>(std::numeric_limits<I>::min());
        double max = static_cast<double>(std::numeric_limits<I>::max());

        if constexpr (std::is_same_v<F, float>)
        {
            vec2<double> preciseVec = vec2<double>(static_cast<double>(x), static_cast<double>(y));

            return iVec2<I>(
                static_cast<I>(std::clamp(std::ceil(preciseVec.x), min, max)),
                static_cast<I>(std::clamp(std::ceil(preciseVec.y), min, max))
            );
        }
        else
        {
            return iVec2<I>(
                static_cast<I>(std::clamp(std::ceil(x), min, max)),
                static_cast<I>(std::clamp(std::ceil(y), min, max))
            );
        }
    }
    
    template<FloatingNumber F>
    template<IntegralNumber I>
    inline iVec2<I> vec2<F>::roundTo() const noexcept
    {
        double min = static_cast<double>(std::numeric_limits<I>::min());
        double max = static_cast<double>(std::numeric_limits<I>::max());

        if constexpr (std::is_same_v<F, float>)
        {
            vec2<double> preciseVec = vec2<double>(static_cast<double>(x), static_cast<double>(y));

            return iVec2<I>(
                static_cast<I>(std::clamp(std::round(preciseVec.x), min, max)),
                static_cast<I>(std::clamp(std::round(preciseVec.y), min, max))
            );
        }
        else
        {
            return iVec2<I>(
                static_cast<I>(std::clamp(std::round(x), min, max)),
                static_cast<I>(std::clamp(std::round(y), min, max))
            );
        }
    }


    template<FloatingNumber F>
    inline constexpr vec2<F> vec2<F>::projectOnto(const vec2<F>& base) const noexcept
    {
        F lSq = base.lengthSquared();

        if (lSq < glMath::epsilon<F>()) return base;
        
        F scalar = vec2<F>::dotProduct(*this, base) / lSq;

        return base * scalar;
    }


    template<FloatingNumber F>
    inline F vec2<F>::length() const noexcept
    {
        if constexpr (std::is_same_v<F, float>)
        {
            return std::sqrtf( (x * x) + (y * y) );
        }
        else
        {
            return std::sqrt( (x * x) + (y * y) );
        }
    }

    template<FloatingNumber F>
    inline constexpr F vec2<F>::lengthSquared() const noexcept
    {
        return (x * x) + (y * y);
    }

    template<FloatingNumber F>
    inline constexpr F vec2<F>::dotProduct(const vec2& other) const noexcept
    {
        return (other.x * x) + (other.y * y);
    }

    template<FloatingNumber F>
    inline constexpr F vec2<F>::crossProduct(const vec2& other) const noexcept
    {
        return (x * other.y) - (other.x * y);
    }

    template<FloatingNumber F>
    inline F vec2<F>::distance(const vec2& other) const noexcept
    {
        F xx = other.x - x;
        F yy = other.y - y;

        F xxyy = xx * xx - yy * yy;

        if constexpr (std::is_same_v<F, float>)
        {
            return std::sqrtf( xxyy );
        }
        else
        {
            return std::sqrt( xxyy );
        }
    }

    template<FloatingNumber F>
    inline constexpr F vec2<F>::distanceSquared(const vec2& other) const noexcept
    {
        F xx = other.x - x;
        F yy = other.y - y;

        return xx * xx - yy * yy;
    }

    template<FloatingNumber F>
    inline constexpr vec2<F> vec2<F>::min(const vec2<F>& other) const noexcept
    {
        return vec2<F>(glMath::min(x, other.x), glMath::min(y, other.y));
    }
    template<FloatingNumber F>
    inline constexpr vec2<F> vec2<F>::max(const vec2<F>& other) const noexcept
    {
        return vec2<F>(glMath::max(x, other.x), glMath::max(y, other.y));
    }

    #pragma endregion MemberMethods

    #pragma region StaticMethods

    template<FloatingNumber F>
    inline F vec2<F>::angleBetween(const vec2<F>& a, const vec2<F>& b) noexcept
    {
        F dot = std::clamp( vec2<F>::dotProduct(a.getNormalizedVec(), b.getNormalizedVec()), static_cast<F>(-1.0), static_cast<F>(1.0) );
    
        if constexpr (std::is_same_v<F, float>)
        {
            return std::acosf(dot);
        }
        else
        {
            return std::acos(dot);
        }

    }


    template<FloatingNumber F>
    inline vec2<F> vec2<F>::normalized(const vec2<F>& vec) noexcept
    {
        return vec.getNormalizedVec();
    }


    template<FloatingNumber F>
    inline F vec2<F>::length(const vec2<F>& vec) noexcept
    {
        return vec.length();
    }

    template<FloatingNumber F>
    inline constexpr F vec2<F>::lengthSquared(const vec2& vec) noexcept
    {
        return vec.lengthSquared();
    }

    template<FloatingNumber F>
    inline constexpr F vec2<F>::dotProduct(const vec2& a, const vec2& b) noexcept
    {
        return (a.x * b.x) + (a.y * b.y);
    }

    template<FloatingNumber F>
    inline constexpr F vec2<F>::crossProduct(const vec2& a, const vec2& b) noexcept
    {
        return (a.x * b.y) - (a.y * b.x);
    }

    template<FloatingNumber F>
    inline F vec2<F>::distance(const vec2& a, const vec2& b) noexcept
    {
        return a.distance(b);
    }

    template<FloatingNumber F>
    inline constexpr F vec2<F>::distanceSquared(const vec2& a, const vec2& b) noexcept
    {
        return a.distanceSquared(b);
    }

    template<FloatingNumber F>
    inline constexpr vec2<F> vec2<F>::project(const vec2<F>& proj, const vec2& base) noexcept
    {
        F lSq = base.lengthSquared();

        if (lSq < glMath::epsilon<F>()) return base;
        
        F scalar = vec2<F>::dotProduct(proj, base) / lSq;

        return base * scalar;
    }


    template<FloatingNumber F>
    inline constexpr vec2<F> vec2<F>::min(const vec2<F>& a, const vec2<F>& b) noexcept
    {
        return vec2<F>(glMath::min(a.x, b.x), glMath::min(a.y, b.y));
    }
    template<FloatingNumber F>
    inline constexpr vec2<F> vec2<F>::max(const vec2<F>& a, const vec2<F>& b) noexcept
    {
        return vec2<F>(glMath::max(a.x, b.x), glMath::max(a.y, b.y));
    }

    template<FloatingNumber F>
    inline constexpr vec2<F> vec2<F>::lerp(const vec2<F>& start, const vec2<F>& end, F t) noexcept
    {
        t = glMath::clamp01(t);
        return vec2<F>( start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t );
    }

    template<FloatingNumber F>
    inline constexpr vec2<F> vec2<F>::lerpUnclamped(const vec2<F>& start, const vec2<F>& end, F t) noexcept
    {
        return vec2<F>(start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t);
    }


    template<FloatingNumber F>
    inline constexpr vec2<F> vec2<F>::slerp(const vec2<F>& start, const vec2<F>& end, F t) noexcept
    {
        t = glMath::clamp01(t);
        return vec2<F>::slerpUnclamped(start, end, t);
    }
    template<FloatingNumber F>
    inline constexpr vec2<F> vec2<F>::slerpUnclamped(const vec2<F>& start, const vec2<F>& end, F t) noexcept
    {
        F dot = vec2<F>::dotProduct(start, end);

        if (dot > static_cast<F>(0.9995))
        {
            return vec2<F>::lerpUnclamped(start, end, t);
        }

        if constexpr (std::is_same_v<F, float>)
        {
            F ang = std::acosf(dot);
            F sinAng = std::sinf(ang);
    
            F wA = std::sinf((1.0f - t) * ang) / sinAng;
            F wB = std::sinf(t * ang) / sinAng;
    
            return (start * wA) + (end * wB);
        }
        else
        {
            F ang = std::acos(dot);
            F sinAng = std::sin(ang);
    
            F wA = std::sin((1.0 - t) * ang) / sinAng;
            F wB = std::sin(t * ang) / sinAng;
    
            return (start * wA) + (end * wB);
        }

    }


    #pragma endregion StaticMethods

    #pragma region ReferenceOperators

    template<FloatingNumber F>
    inline constexpr vec2<F>& vec2<F>::operator+=(const vec2<F>& other) noexcept
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }

    template<FloatingNumber F>
    inline constexpr vec2<F>& vec2<F>::operator-=(const vec2<F>& other) noexcept
    {
        this->x -= other.x;
        this->y -= other.y;

        return *this;
    }

    template<FloatingNumber F>
    inline constexpr vec2<F>& vec2<F>::operator*=(F scalar) noexcept
    {
        this->x *= scalar;
        this->y *= scalar;

        return *this;
    }


    template<FloatingNumber F>
    inline constexpr vec2<F>& vec2<F>::operator/=(F scalar) noexcept
    {
        if (std::abs(scalar) > glMath::epsilon<F>())
        {
            F invScalar = static_cast<F>(1.0) / scalar;

            this->x *= invScalar;
            this->y *= invScalar;
        }

        return *this;
    }

    template<FloatingNumber F>
    inline const F* vec2<F>::valuePtr() const noexcept
    {
        return &data[0];
    }

    #pragma endregion ReferenceOperators

    #pragma region ArithmeticOperators

    template<FloatingNumber F>
    inline constexpr vec2<F> operator+(const vec2<F>& a, const vec2<F>& b) noexcept
    {
        return vec2(a.x + b.x, a.y + b.y);
    }
    template<FloatingNumber F>
    inline constexpr vec2<F> operator+(const vec2<F>& a, F scalar) noexcept
    {
        return vec2(a.x + scalar, a.y + scalar);
    }

    template<FloatingNumber F>
    inline constexpr vec2<F> operator-(const vec2<F>& a, const vec2<F>& b) noexcept
    {
        return vec2(a.x - b.x, a.y - b.y);
    }
    template<FloatingNumber F>
    inline constexpr vec2<F> operator-(const vec2<F>& a, F scalar) noexcept
    {
        return vec2(a.x - scalar, a.y - scalar);
    }
    

    template <FloatingNumber F>
    inline constexpr vec2<F> vec2<F>::operator-() const noexcept
    {
        return vec2(-x, -y);
    }


    template<FloatingNumber F>
    inline constexpr vec2<F> operator*(const vec2<F>& a, const vec2<F>& b) noexcept
    {
        return vec2(a.x * b.x, a.y * b.y);
    }
    template<FloatingNumber F>
    inline constexpr vec2<F> operator*(const vec2<F>& vec, F scalar) noexcept
    {
        return vec2(vec.x * scalar, vec.y * scalar);
    }
    template<FloatingNumber F>
    inline constexpr vec2<F> operator*(F scalar, const vec2<F>& vec) noexcept
    {
        return vec2(vec.x * scalar, vec.y * scalar);
    }

    template<FloatingNumber F>
    inline constexpr vec2<F> operator/(const vec2<F>& vec, F scalar) noexcept
    {
        if (std::abs(scalar) < glMath::epsilon<F>()) return vec;

        F invScalar = static_cast<F>(1.0) / scalar;

        return vec2(vec.x * invScalar, vec.y * invScalar);
    }


    template<FloatingNumber F>
    inline constexpr bool operator==(const vec2<F>& a, const vec2<F>& b) noexcept
    {
        return static_cast<F>( std::abs(b.x - a.x) ) < glMath::epsilon<F>() &&
               static_cast<F>( std::abs(b.y - a.y) ) < glMath::epsilon<F>();
    }

    template<FloatingNumber F>
    inline constexpr bool operator!=(const vec2<F>& a, const vec2<F>& b) noexcept
    {
        return !(a == b);
    }

    #pragma endregion ArithmeticOperators

}

