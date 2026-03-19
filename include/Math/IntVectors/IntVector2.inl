#include <concepts>
#include <cmath>

#include <algorithm>

#include "Math\MathInternal.hpp"


namespace glMath
{
    #pragma region Constructors

    template<IntegralNumber I>
    inline iVec2<I>::iVec2()
        : x(0), y(0)
    {}
    template<IntegralNumber I>
    inline iVec2<I>::iVec2(I scalar)
        : x(scalar), y(scalar)
    {}
    template<IntegralNumber I>
    inline iVec2<I>::iVec2(I vx, I vy)
        : x(vx), y(vy)
    {}
    template<IntegralNumber I>
    inline iVec2<I>::iVec2(const iVec2<I>& vec)
        : x(vec.x), y(vec.y)
    {}

    #pragma endregion

    #pragma region StaticMethods

    template<IntegralNumber I>
    inline I iVec2<I>::lengthSquared(const iVec2<I>& vec) 
    {
        return (vec.x * vec.x) + (vec.y * vec.y);
    }

    template<IntegralNumber I>
    inline I iVec2<I>::distanceSquared(const iVec2<I>& a, const iVec2<I>& b) 
    {
        return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
    }

    template<IntegralNumber I>
    inline I iVec2<I>::dotProduct(const iVec2<I>& a, const iVec2<I>& b)
    {
        return (a.x * b.x) + (a.y * b.y);
    }

    template<IntegralNumber I>
    inline iVec2<I> iVec2<I>::clamp(const iVec2<I>& vec, I minInclusive, I maxInclusive)
    {
        return vec.getClampedVec(minInclusive, maxInclusive);
    }

    template<IntegralNumber I>
    inline iVec2<I> iVec2<I>::abs(const iVec2<I>& vec)
    {
        return vec.getAbsValueVec();
    }

    template<IntegralNumber I>
    inline iVec2<I> iVec2<I>::min(const iVec2<I>& a, const iVec2<I>& b)
    {
        return iVec2<I>(glMath::min(a.x, b.x), glMath::min(a.y, b.y));
    }
    template<IntegralNumber I>
    inline iVec2<I> iVec2<I>::max(const iVec2<I>& a, const iVec2<I>& b)
    {
        return iVec2<I>(glMath::max(a.x, b.x), glMath::max(a.y, b.y));
    }


    template<IntegralNumber I>
    template<FloatingNumber F>
    inline iVec2<I> iVec2<I>::floor(const vec2<F>& fVec)
    {
        return iVec2<I>(std::floor(fVec.x), std::floor(fVec.y));
    }
    template<IntegralNumber I>
    template<FloatingNumber F>
    inline iVec2<I> iVec2<I>::ceil(const vec2<F>& fVec)
    {
        return iVec2<I>(std::ceil(fVec.x), std::ceil(fVec.y));
    }
    template<IntegralNumber I>
    template<FloatingNumber F>
    inline iVec2<I> iVec2<I>::round(const vec2<F>& fVec)
    {
        return iVec2<I>(std::round(fVec.x), std::round(fVec.y));
    }

    #pragma endregion


    #pragma region MemberMethods


    template<IntegralNumber I>
    template<IntegralNumber i>
    inline iVec2<i> iVec2<I>::as() const
    {
        std::numeric_limits<i> limit = std::numeric_limits<i>();
        I minLimit = static_cast<I>(limit.lowest());
        I maxLimit = static_cast<I>(limit.max());

        return iVec2<i>(
            static_cast<i>(std::clamp(x, minLimit, maxLimit)),
            static_cast<i>(std::clamp(y, minLimit, maxLimit))
        );
    }

    template<IntegralNumber I>
    inline const I* iVec2<I>::valuePtr() const
    {
        return &x;
    }


    template<IntegralNumber I>
    inline I iVec2<I>::lengthSquared() const
    {
        return (x * x) + (y * y);
    }

    template<IntegralNumber I>
    inline I iVec2<I>::distanceSquared(const iVec2<I>& other) const
    {
        return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y);
    }

    template<IntegralNumber I>
    inline I iVec2<I>::dotProduct(const iVec2<I>& other) const
    {
        return (x * other.x) + (y * other.y);
    }


    template<IntegralNumber I>
    inline iVec2<I>& iVec2<I>::clamp(I minInclusive, I maxInclusive)
    {
        x = glMath::clamp(x, minInclusive, maxInclusive);
        y = glMath::clamp(y, minInclusive, maxInclusive);

        return *this;
    }
    template<IntegralNumber I>
    inline iVec2<I> iVec2<I>::getClampedVec(I minInclusive, I maxInclusive) const
    {
        iVec2<I> copy = *this;

        return copy.clamp(minInclusive, maxInclusive);
    }

    template<IntegralNumber I>
    inline iVec2<I>& iVec2<I>::absValue()
    {
        x = std::abs(x);
        y = std::abs(y);

        return *this;
    }
    template<IntegralNumber I>
    inline iVec2<I> iVec2<I>::getAbsValueVec() const
    {
        iVec2<I> copy = *this;

        return copy.absValue();
    }

    template<IntegralNumber I>
    inline iVec2<I> iVec2<I>::min(const iVec2<I>& other) const
    {
        return iVec2<I>(glMath::min(x, other.x), glMath::min(y, other.y));
    }
    template<IntegralNumber I>
    inline iVec2<I> iVec2<I>::max(const iVec2<I>& other) const
    {
        return iVec2<I>(glMath::max(x, other.x), glMath::max(y, other.y));
    }

    #pragma endregion


    #pragma region ReferenceOperators

    template<IntegralNumber I>
    inline iVec2<I>& iVec2<I>::operator+=(const iVec2<I>& vec)
    {
        x += vec.x;
        y += vec.y;

        return *this;
    }
    template<IntegralNumber I>
    inline iVec2<I>& iVec2<I>::operator+=(I scalar)
    {
        x += scalar;
        y += scalar;

        return *this;
    }

    template<IntegralNumber I>
    inline iVec2<I>& iVec2<I>::operator-=(const iVec2<I>& vec)
    {
        x -= vec.x;
        y -= vec.y;

        return *this;
    }
    template<IntegralNumber I>
    inline iVec2<I>& iVec2<I>::operator-=(I scalar)
    {
        x -= scalar;
        y -= scalar;

        return *this;
    }

    template<IntegralNumber I>
    inline iVec2<I>& iVec2<I>::operator*=(const iVec2<I>& vec)
    {
        x *= vec.x;
        y *= vec.y;

        return *this;
    }
    template<IntegralNumber I>
    inline iVec2<I>& iVec2<I>::operator*=(I scalar)
    {
        x *= scalar;
        y *= scalar;

        return *this;
    }

    template<IntegralNumber I>
    inline iVec2<I>& iVec2<I>::operator/=(I scalar)
    {
        if (scalar != 0)
        {
            x /= scalar;
            y /= scalar;
        }

        return *this;
    }

    template<IntegralNumber I>
    inline iVec2<I>& iVec2<I>::operator%=(I scalar)
    {
        x %= scalar;
        y %= scalar;

        return *this;
    }

    #pragma endregion

    #pragma region Operators

    template<IntegralNumber I>
    inline I& iVec2<I>::operator[](I index) 
    {
        return data[index];
    }


    template<IntegralNumber I>
    inline iVec2<I> iVec2<I>::operator-() const
    {
        return iVec2<I>(-x, -y);
    }


    template<IntegralNumber I>
    inline iVec2<I> operator+(const iVec2<I>& a, const iVec2<I>& b)
    {
        return iVec2<I>(a.x + b.x, a.y + b.y);
    }
    template<IntegralNumber I>
    inline iVec2<I> operator+(const iVec2<I>& a, I scalar)
    {
        return iVec2<I>(a.x + scalar, a.y + scalar);
    }

    template<IntegralNumber I>
    inline iVec2<I> operator-(const iVec2<I>& a, const iVec2<I>& b)
    {
        return iVec2<I>(a.x - b.x, a.y - b.y);
    }
    template<IntegralNumber I>
    inline iVec2<I> operator-(const iVec2<I>& a, I scalar)
    {
        return iVec2<I>(a.x - scalar, a.y - scalar);
    }

    template<IntegralNumber I>
    inline iVec2<I> operator*(const iVec2<I>& a, const iVec2<I>& b)
    {
        return iVec2<I>(a.x * b.x, a.y * b.y);
    }
    template<IntegralNumber I>
    inline iVec2<I> operator*(const iVec2<I>& a, I scalar)
    {
        return iVec2<I>(a.x * scalar, a.y * scalar);
    }
    template<IntegralNumber I>
    inline iVec2<I> operator*(I scalar, const iVec2<I>& a)
    {
        return iVec2<I>(a.x * scalar, a.y * scalar);
    }

    template<IntegralNumber I>
    inline iVec2<I> operator/(const iVec2<I>& vec, I scalar)
    {
        if (scalar == 0) return vec;

        return iVec2<I>(vec.x / scalar, vec.y / scalar);
    }

    template<IntegralNumber I>
    inline iVec2<I> operator%(const iVec2<I>& vec, I scalar)
    {
        return iVec2<I>(vec.x % scalar, vec.y % scalar);
    }


    template<IntegralNumber I>
    inline bool operator==(const iVec2<I>& a, const iVec2<I>& b)
    {
        return a.x == b.x &&
               a.y == b.y;
    }
    template<IntegralNumber I>
    inline bool operator!=(const iVec2<I>& a, const iVec2<I>& b)
    {
        return !(a == b);
    }

    template<IntegralNumber I>
    inline bool operator<(const iVec2<I>& a, const iVec2<I>& b)
    {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    }
    template<IntegralNumber I>
    inline bool operator>(const iVec2<I>& a, const iVec2<I>& b)
    {
        if (a.x != b.x) return a.x > b.x;
        return a.y > b.y;
    }

    template<IntegralNumber I>
    inline bool operator<=(const iVec2<I>& a, const iVec2<I>& b)
    {
        if (a.x != b.x) return a.x <= b.x;
        return a.y <= b.y;
    }
    template<IntegralNumber I>
    inline bool operator>=(const iVec2<I>& a, const iVec2<I>& b)
    {
        if (a.x != b.x) return a.x >= b.x;
        return a.y >= b.y;
    }

    #pragma endregion   

}

