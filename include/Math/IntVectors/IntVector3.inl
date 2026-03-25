#include <concepts>
#include <cmath>

#include "Math\MathInternal.hpp"


namespace glMath
{
    #pragma region Constructors

    template<IntegralNumber I>
    inline iVec3<I>::iVec3()
        : x(static_cast<I>(0)), y(static_cast<I>(0)), z(static_cast<I>(0))
    {}
    template<IntegralNumber I>    
    inline iVec3<I>::iVec3(I scalar)
        : x(scalar), y(scalar), z(scalar)
    {}
    template<IntegralNumber I>    
    inline iVec3<I>::iVec3(I vx, I vy, I vz)
        : x(vx), y(vy), z(vz)
    {}
    template<IntegralNumber I>    
    inline iVec3<I>::iVec3(const iVec3<I>& vec)
        : x(vec.x), y(vec.y), z(vec.z)
    {}

    #pragma endregion

    
    #pragma region StaticMethods


    template<IntegralNumber I>
    inline I iVec3<I>::iDistance(const iVec3<I>& a, const iVec3<I>& b) 
    {
        return std::abs(b.x - a.x) + std::abs(b.y - a.y) + std::abs(b.z - a.z);
    }

    template<IntegralNumber I>
    template<FloatingNumber F>
    inline F iVec3<I>::distance(const iVec3<I>& a, const iVec3<I>& b) 
    {
        F ax = static_cast<F>(a.x);
        F ay = static_cast<F>(a.y);
        F az = static_cast<F>(a.y);
        F bx = static_cast<F>(b.x);
        F by = static_cast<F>(b.y);
        F bz = static_cast<F>(b.y);

        if constexpr (std::is_same_v<F, float>)
        {
            return std::sqrtf( (bx - ax) * (bx - ax) + (by - ay) * (by - ay) * (bz - az) * (bz - az) );
        }
        else 
        {
            return std::sqrt( (bx - ax) * (bx - ax) + (by - ay) * (by - ay) * (bz - az) * (bz - az) );
        }
    }

    template<IntegralNumber I>
    template<FloatingNumber F>
    inline F iVec3<I>::length(const iVec3<I>& vec) 
    {
        F vx = static_cast<F>(vec.x);
        F vy = static_cast<F>(vec.y);
        F vz = static_cast<F>(vec.z);

        if constexpr (std::is_same_v<F, float>)
        {
            return std::sqrtf( (vx * vx) + (vy * vy) + (vz * vz) );
        }
        else 
        {
            return std::sqrt( (vx * vx) + (vy * vy) + (vz * vz) );
        }
    }

    template<IntegralNumber I>
    inline I iVec3<I>::lengthSquared(const iVec3<I>& vec) 
    {
        return (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
    }

    template<IntegralNumber I>
    inline I iVec3<I>::distanceSquared(const iVec3<I>& a, const iVec3<I>& b) 
    {
        return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z - a.z) * (b.z - a.z);
    }

    template<IntegralNumber I>
    inline I iVec3<I>::dotProduct(const iVec3<I>& a, const iVec3<I>& b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    template<IntegralNumber I>
    inline iVec3<I> iVec3<I>::crossProduct(const iVec3<I>& a, const iVec3<I>& b)
    {
        I vx = a.y * b.z - a.z * b.y;
        I vy = a.z * b.x - a.x * b.z;
        I vz = a.x * b.y - a.y * b.x;

        return iVec3<I>(vx, vy, vz);
    }


    template<IntegralNumber I>
    inline iVec3<I> iVec3<I>::clamp(const iVec3<I>& vec, I minInclusive, I maxInclusive)
    {
        return vec.getClampedVec(minInclusive, maxInclusive);
    }

    template<IntegralNumber I>
    inline iVec3<I> iVec3<I>::abs(const iVec3<I>& vec)
    {
        return vec.getAbsValueVec();
    }

    template<IntegralNumber I>
    inline iVec3<I> iVec3<I>::min(const iVec3<I>& a, const iVec3<I>& b)
    {
        return iVec3<I>(glMath::min(a.x, b.x), glMath::min(a.y, b.y), glMath::min(a.z, b.z));
    }
    template<IntegralNumber I>
    inline iVec3<I> iVec3<I>::max(const iVec3<I>& a, const iVec3<I>& b)
    {
        return iVec3<I>(glMath::max(a.x, b.x), glMath::max(a.y, b.y), glMath::max(a.z, b.z));
    }


    template<IntegralNumber I>
    template<FloatingNumber F>
    inline iVec3<I> iVec3<I>::floor(const vec3<F>& fVec)
    {
        double min = static_cast<double>(std::numeric_limits<I>::min());
        double max = static_cast<double>(std::numeric_limits<I>::max());

        if constexpr (std::is_same_v<F, float>)
        {
            vec3<double> preciseVec = vec3<double>(static_cast<double>(fVec.x), static_cast<double>(fVec.y));

            return iVec3<I>(
                static_cast<I>(std::clamp(std::floor(preciseVec.x), min, max)),
                static_cast<I>(std::clamp(std::floor(preciseVec.y), min, max)),
                static_cast<I>(std::clamp(std::floor(preciseVec.z), min, max))
            );
        }
        else
        {
            return iVec3<I>(
                static_cast<I>(std::clamp(std::floor(fVec.x), min, max)),
                static_cast<I>(std::clamp(std::floor(fVec.y), min, max)),
                static_cast<I>(std::clamp(std::floor(fVec.z), min, max))
            );
        }


        // return iVec2<I>(std::floor(fVec.x), std::floor(fVec.y));
    }
    template<IntegralNumber I>
    template<FloatingNumber F>
    inline iVec3<I> iVec3<I>::ceil(const vec3<F>& fVec)
    {
        double min = static_cast<double>(std::numeric_limits<I>::min());
        double max = static_cast<double>(std::numeric_limits<I>::max());

        if constexpr (std::is_same_v<F, float>)
        {
            vec3<double> preciseVec = vec3<double>(static_cast<double>(fVec.x), static_cast<double>(fVec.y));

            return iVec3<I>(
                static_cast<I>(std::clamp(std::ceil(preciseVec.x), min, max)),
                static_cast<I>(std::clamp(std::ceil(preciseVec.y), min, max)),
                static_cast<I>(std::clamp(std::ceil(preciseVec.z), min, max))
            );
        }
        else
        {
            return iVec3<I>(
                static_cast<I>(std::clamp(std::ceil(fVec.x), min, max)),
                static_cast<I>(std::clamp(std::ceil(fVec.y), min, max)),
                static_cast<I>(std::clamp(std::ceil(fVec.z), min, max))
            );
        }


        // return iVec2<I>(std::floor(fVec.x), std::floor(fVec.y));
    }
    template<IntegralNumber I>
    template<FloatingNumber F>
    inline iVec3<I> iVec3<I>::round(const vec3<F>& fVec)
    {
        double min = static_cast<double>(std::numeric_limits<I>::min());
        double max = static_cast<double>(std::numeric_limits<I>::max());

        if constexpr (std::is_same_v<F, float>)
        {
            vec3<double> preciseVec = vec3<double>(static_cast<double>(fVec.x), static_cast<double>(fVec.y));

            return iVec3<I>(
                static_cast<I>(std::clamp(std::round(preciseVec.x), min, max)),
                static_cast<I>(std::clamp(std::round(preciseVec.y), min, max)),
                static_cast<I>(std::clamp(std::round(preciseVec.z), min, max))
            );
        }
        else
        {
            return iVec3<I>(
                static_cast<I>(std::clamp(std::round(fVec.x), min, max)),
                static_cast<I>(std::clamp(std::round(fVec.y), min, max)),
                static_cast<I>(std::clamp(std::round(fVec.z), min, max))
            );
        }


        // return iVec2<I>(std::floor(fVec.x), std::floor(fVec.y));
    }

    #pragma endregion


    #pragma region MemberMethods


    template<IntegralNumber I>
    inline I iVec3<I>::iDistance(const iVec3<I>& other) const
    {
        return std::abs(other.x - x) + std::abs(other.y - y) + std::abs(other.z - z);
    }

    template<IntegralNumber I>
    template<FloatingNumber F>
    inline F iVec3<I>::distance(const iVec3<I>& other) const
    {
        F ax = static_cast<F>(x);
        F ay = static_cast<F>(y);
        F az = static_cast<F>(y);
        F bx = static_cast<F>(other.x);
        F by = static_cast<F>(other.y);
        F bz = static_cast<F>(other.y);

        if constexpr (std::is_same_v<F, float>)
        {
            return std::sqrtf( (bx - ax) * (bx - ax) + (by - ay) * (by - ay) * (bz - az) * (bz - az) );
        }
        else 
        {
            return std::sqrt( (bx - ax) * (bx - ax) + (by - ay) * (by - ay) * (bz - az) * (bz - az) );
        }
    }

    template<IntegralNumber I>
    template<FloatingNumber F>
    inline F iVec3<I>::length() const
    {
        F vx = static_cast<F>(x);
        F vy = static_cast<F>(y);
        F vz = static_cast<F>(z);

        if constexpr (std::is_same_v<F, float>)
        {
            return std::sqrtf( (vx * vx) + (vy * vy) + (vz * vz) );
        }
        else 
        {
            return std::sqrt( (vx * vx) + (vy * vy) + (vz * vz) );
        }
    }

    template<IntegralNumber I>
    template<IntegralNumber i>
    inline iVec3<i> iVec3<I>::as() const
    {
        std::numeric_limits<i> limit = std::numeric_limits<i>();
        I minLimit = static_cast<I>(limit.lowest());
        I maxLimit = static_cast<I>(limit.max());
    
        return iVec3<i>(
            static_cast<i>(std::clamp(x, minLimit, maxLimit)),
            static_cast<i>(std::clamp(y, minLimit, maxLimit)),
            static_cast<i>(std::clamp(z, minLimit, maxLimit))
        );
    }
    template<IntegralNumber I>
    template<FloatingNumber F>
    inline vec3<F> iVec3<I>::to() const
    {
        return vec3<F>(
            static_cast<F>(x),
            static_cast<F>(y),
            static_cast<F>(z)
        );
    }


    template<IntegralNumber I>
    inline const I* iVec3<I>::valuePtr() const
    {
        return &x;
    }


    template<IntegralNumber I>
    inline I iVec3<I>::lengthSquared() const
    {
        return (x * x) + (y * y) + (z * z);
    }

    template<IntegralNumber I>
    inline I iVec3<I>::distanceSquared(const iVec3<I>& other) const
    {
        return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) + (other.z - z) * (other.z - z);
    }

    template<IntegralNumber I>
    inline I iVec3<I>::dotProduct(const iVec3<I>& other) const
    {
        return (x * other.x) + (y * other.y) + (z * other.z);
    }

    template<IntegralNumber I>
    inline iVec3<I> iVec3<I>::crossProduct(const iVec3<I>& other) const
    {
        I vx = y * other.z - z * other.y;
        I vy = z * other.x - x * other.z;
        I vz = x * other.y - y * other.x;

        return iVec3<I>(vx, vy, vz);
    }


    template<IntegralNumber I>
    inline iVec3<I>& iVec3<I>::clamp(I minInclusive, I maxInclusive)
    {
        x = glMath::clamp(x, minInclusive, maxInclusive);
        y = glMath::clamp(y, minInclusive, maxInclusive);
        z = glMath::clamp(z, minInclusive, maxInclusive);

        return *this;
    }
    template<IntegralNumber I>
    inline iVec3<I> iVec3<I>::getClampedVec(I minInclusive, I maxInclusive) const
    {
        iVec3<I> copy = *this;

        return copy.clamp(minInclusive, maxInclusive);
    }

    template<IntegralNumber I>
    inline iVec3<I>& iVec3<I>::absValue()
    {
        x = std::abs(x);
        y = std::abs(y);
        z = std::abs(z);

        return *this;
    }
        
    template<IntegralNumber I>
    inline iVec3<I> iVec3<I>::getAbsValueVec() const
    {
        iVec3<I> copy = *this;

        return copy.absValue();
    }

    template<IntegralNumber I>
    inline iVec3<I> iVec3<I>::min(const iVec3<I>& other) const
    {
        return iVec3<I>(glMath::min(x, other.x), glMath::min(y, other.y), glMath::min(z, other.z));
    }
    template<IntegralNumber I>
    inline iVec3<I> iVec3<I>::max(const iVec3<I>& other) const
    {
        return iVec3<I>(glMath::max(x, other.x), glMath::max(y, other.y), glMath::max(z, other.z));
    }

    #pragma endregion


    #pragma region ReferenceOperators

    template<IntegralNumber I>
    inline iVec3<I>& iVec3<I>::operator+=(const iVec3<I>& vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;

        return *this;
    }
    template<IntegralNumber I>
    inline iVec3<I>& iVec3<I>::operator+=(I scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;

        return *this;
    }

    template<IntegralNumber I>
    inline iVec3<I>& iVec3<I>::operator-=(const iVec3<I>& vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;

        return *this;
    }
    template<IntegralNumber I>
    inline iVec3<I>& iVec3<I>::operator-=(I scalar)
    {
        x -= scalar;
        y -= scalar;
        z -= scalar;

        return *this;
    }

    template<IntegralNumber I>
    inline iVec3<I>& iVec3<I>::operator*=(const iVec3<I>& vec)
    {
        x *= vec.x;
        y *= vec.y;
        z *= vec.z;

        return *this;
    }
    template<IntegralNumber I>
    inline iVec3<I>& iVec3<I>::operator*=(I scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }

    template<IntegralNumber I>
    inline iVec3<I>& iVec3<I>::operator/=(I scalar)
    {
        if (scalar != 0)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
        }

        return *this;
    }

    template<IntegralNumber I>
    inline iVec3<I>& iVec3<I>::operator%=(I scalar)
    {
        x %= scalar;
        y %= scalar;
        z %= scalar;

        return *this;
    }

    #pragma endregion

    #pragma region Operators

    template<IntegralNumber I>
    inline iVec3<I> iVec3<I>::operator-() const
    {
        return iVec3<I>(-x, -y, -z);
    }


    template<IntegralNumber I>
    inline iVec3<I> operator+(const iVec3<I>& a, const iVec3<I>& b)
    {
        return iVec3<I>(a.x + b.x, a.y + b.y, a.z + b.z);
    }
    template<IntegralNumber I>
    inline iVec3<I> operator+(const iVec3<I>& a, I scalar)
    {
        return iVec3<I>(a.x + scalar, a.y + scalar, a.z + scalar);
    }

    template<IntegralNumber I>
    inline iVec3<I> operator-(const iVec3<I>& a, const iVec3<I>& b)
    {
        return iVec3<I>(a.x - b.x, a.y - b.y, a.z - b.z);
    }
    template<IntegralNumber I>
    inline iVec3<I> operator-(const iVec3<I>& a, I scalar)
    {
        return iVec3<I>(a.x - scalar, a.y - scalar, a.z - scalar);
    }

    template<IntegralNumber I>
    inline iVec3<I> operator*(const iVec3<I>& a, const iVec3<I>& b)
    {
        return iVec3<I>(a.x * b.x, a.y * b.y, a.z * b.z);
    }
    template<IntegralNumber I>
    inline iVec3<I> operator*(const iVec3<I>& a, I scalar)
    {
        return iVec3<I>(a.x * scalar, a.y * scalar, a.z * scalar);
    }
    template<IntegralNumber I>
    inline iVec3<I> operator*(I scalar, const iVec3<I>& a)
    {
        return iVec3<I>(a.x * scalar, a.y * scalar, a.z * scalar);
    }

    template<IntegralNumber I>
    inline iVec3<I> operator/(const iVec3<I>& vec, I scalar)
    {
        if (scalar == 0) return vec;

        return iVec3<I>(vec.x / scalar, vec.y / scalar, vec.z / scalar);
    }

    template<IntegralNumber I>
    inline iVec3<I> operator%(const iVec3<I>& vec, I scalar)
    {
        return iVec3<I>(vec.x % scalar, vec.y % scalar, vec.z % scalar);
    }


    template<IntegralNumber I>
    inline bool operator==(const iVec3<I>& a, const iVec3<I>& b)
    {
        return a.x == b.x &&
               a.y == b.y &&
               a.z == b.z;
    }
    template<IntegralNumber I>
    inline bool operator!=(const iVec3<I>& a, const iVec3<I>& b)
    {
        return !(a == b);
    }

    template<IntegralNumber I>
    inline bool operator<(const iVec3<I>& a, const iVec3<I>& b)
    {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    }
    template<IntegralNumber I>
    inline bool operator>(const iVec3<I>& a, const iVec3<I>& b)
    {
        if (a.x != b.x) return a.x > b.x;
        if (a.y != b.y) return a.y > b.y;
        return a.z > b.z;
    }

    template<IntegralNumber I>
    inline bool operator<=(const iVec3<I>& a, const iVec3<I>& b)
    {
        if (a.x != b.x) return a.x <= b.x;
        if (a.y != b.y) return a.y <= b.y;
        return a.z <= b.z;
    }
    template<IntegralNumber I>
    inline bool operator>=(const iVec3<I>& a, const iVec3<I>& b)
    {
        if (a.x != b.x) return a.x >= b.x;
        if (a.y != b.y) return a.y >= b.y;
        return a.z >= b.z;
    }

    #pragma endregion  
}
