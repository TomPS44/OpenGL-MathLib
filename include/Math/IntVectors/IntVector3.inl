#include <concepts>
#include <cmath>

#include "Math\MathInternal.hpp"


namespace glMath
{
    #pragma region Constructors

    inline intVec3::intVec3()
        : x(0), y(0), z(0)
    {}
    inline intVec3::intVec3(int scalar)
        : x(scalar), y(scalar), z(scalar)
    {}
    inline intVec3::intVec3(int vx, int vy, int vz)
        : x(vx), y(vy), z(vz)
    {}
    inline intVec3::intVec3(const intVec3& vec)
        : x(vec.x), y(vec.y), z(vec.z)
    {}

    #pragma endregion

    
    #pragma region StaticMethods

    inline int intVec3::lengthSquared(const intVec3& vec) 
    {
        return (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
    }

    inline int intVec3::distanceSquared(const intVec3& a, const intVec3& b) 
    {
        return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z - a.z) * (b.z - a.z);
    }

    inline int intVec3::dotProduct(const intVec3& a, const intVec3& b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }

    inline intVec3 intVec3::crossProduct(const intVec3& a, const intVec3& b)
    {
        int vx = a.y * b.z - a.z * b.y;
        int vy = a.z * b.x - a.x * b.z;
        int vz = a.x * b.y - a.y * b.x;

        return intVec3(vx, vy, vz);
    }


    inline intVec3 intVec3::clamp(const intVec3& vec, int minInclusive, int maxInclusive)
    {
        return vec.getClampedVec(minInclusive, maxInclusive);
    }

    inline intVec3 intVec3::abs(const intVec3& vec)
    {
        return vec.getAbsValueVec();
    }

    inline intVec3 intVec3::min(const intVec3& a, const intVec3& b)
    {
        return intVec3(glMath::min(a.x, b.x), glMath::min(a.y, b.y), glMath::min(a.z, b.z));
    }
    inline intVec3 intVec3::max(const intVec3& a, const intVec3& b)
    {
        return intVec3(glMath::max(a.x, b.x), glMath::max(a.y, b.y), glMath::max(a.z, b.z));
    }


    template<FloatingNumber F>
    inline intVec3 intVec3::floor(const vec3<F>& fVec)
    {
        return intVec3(std::floor(fVec.x), std::floor(fVec.y), std::floor(fVec.z));
    }
    template<FloatingNumber F>
    inline intVec3 intVec3::round(const vec3<F>& fVec)
    {
        return intVec3(std::round(fVec.x), std::round(fVec.y), std::round(fVec.z));
    }
    template<FloatingNumber F>
    inline intVec3 intVec3::toInt(const vec3<F>& fVec)
    {
        return intVec3(static_cast<int>(fVec.x), static_cast<int>(fVec.y), static_cast<int>(fVec.z));
    }

    #pragma endregion


    #pragma region MemberMethods

    // template<IntegraNumber I>
    // template<IntegralNumber i>
    // inline intVec3<i> intVec3<I>::as() const
    // {
    //     std::numeric_limits<i> limit = std::numeric_limits<i>();
    //     I minLimit = static_cast<I>(limit.lowest());
    //     I maxLimit = static_cast<I>(limit.max());
    
    //     return iVec2<i>(
    //         static_cast<i>(std::clamp(x, minLimit, maxLimit)),
    //         static_cast<i>(std::clamp(y, minLimit, maxLimit)),
    //         static_cast<i>(std::clamp(z, minLimit, maxLimit))
    //     );
    // }



    inline const int* intVec3::valuePtr() const
    {
        return &x;
    }


    inline int intVec3::lengthSquared() const
    {
        return (x * x) + (y * y) + (z * z);
    }

    inline int intVec3::distanceSquared(const intVec3& other) const
    {
        return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y) + (other.z - z) * (other.z - z);
    }

    inline int intVec3::dotProduct(const intVec3& other) const
    {
        return (x * other.x) + (y * other.y) + (z * other.z);
    }

    inline intVec3 intVec3::crossProduct(const intVec3& other) const
    {
        int vx = y * other.z - z * other.y;
        int vy = z * other.x - x * other.z;
        int vz = x * other.y - y * other.x;

        return intVec3(vx, vy, vz);
    }


    inline intVec3& intVec3::clamp(int minInclusive, int maxInclusive)
    {
        x = glMath::clamp(x, minInclusive, maxInclusive);
        y = glMath::clamp(y, minInclusive, maxInclusive);
        z = glMath::clamp(z, minInclusive, maxInclusive);

        return *this;
    }
    inline intVec3 intVec3::getClampedVec(int minInclusive, int maxInclusive) const
    {
        intVec3 copy = *this;

        return copy.clamp(minInclusive, maxInclusive);
    }

    inline intVec3& intVec3::absValue()
    {
        x = std::abs(x);
        y = std::abs(y);
        z = std::abs(z);

        return *this;
    }
    inline intVec3 intVec3::getAbsValueVec() const
    {
        intVec3 copy = *this;

        return copy.absValue();
    }

    inline intVec3 intVec3::min(const intVec3& other) const
    {
        return intVec3(glMath::min(x, other.x), glMath::min(y, other.y), glMath::min(z, other.z));
    }
    inline intVec3 intVec3::max(const intVec3& other) const
    {
        return intVec3(glMath::max(x, other.x), glMath::max(y, other.y), glMath::max(z, other.z));
    }

    #pragma endregion


    #pragma region ReferenceOperators

    inline intVec3& intVec3::operator+=(const intVec3& vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;

        return *this;
    }
    inline intVec3& intVec3::operator+=(int scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;

        return *this;
    }

    inline intVec3& intVec3::operator-=(const intVec3& vec)
    {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;

        return *this;
    }
    inline intVec3& intVec3::operator-=(int scalar)
    {
        x -= scalar;
        y -= scalar;
        z -= scalar;

        return *this;
    }

    inline intVec3& intVec3::operator*=(const intVec3& vec)
    {
        x *= vec.x;
        y *= vec.y;
        z *= vec.z;

        return *this;
    }
    inline intVec3& intVec3::operator*=(int scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }

    inline intVec3& intVec3::operator/=(int scalar)
    {
        if (scalar != 0)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
        }

        return *this;
    }

    inline intVec3& intVec3::operator%=(int scalar)
    {
        x %= scalar;
        y %= scalar;
        z %= scalar;

        return *this;
    }

    #pragma endregion

    #pragma region Operators

    inline int& intVec3::operator[](int index) 
    {
        return data[index];
    }


    inline intVec3 intVec3::operator-() const
    {
        return intVec3(-x, -y, -z);
    }


    inline intVec3 operator+(const intVec3& a, const intVec3& b)
    {
        return intVec3(a.x + b.x, a.y + b.y, a.z + b.z);
    }
    inline intVec3 operator+(const intVec3& a, int scalar)
    {
        return intVec3(a.x + scalar, a.y + scalar, a.z + scalar);
    }

    inline intVec3 operator-(const intVec3& a, const intVec3& b)
    {
        return intVec3(a.x - b.x, a.y - b.y, a.z - b.z);
    }
    inline intVec3 operator-(const intVec3& a, int scalar)
    {
        return intVec3(a.x - scalar, a.y - scalar, a.z - scalar);
    }

    inline intVec3 operator*(const intVec3& a, const intVec3& b)
    {
        return intVec3(a.x * b.x, a.y * b.y, a.z * b.z);
    }
    inline intVec3 operator*(const intVec3& a, int scalar)
    {
        return intVec3(a.x * scalar, a.y * scalar, a.z * scalar);
    }
    inline intVec3 operator*(int scalar, const intVec3& a)
    {
        return intVec3(a.x * scalar, a.y * scalar, a.z * scalar);
    }

    inline intVec3 operator/(const intVec3& vec, int scalar)
    {
        if (scalar == 0) return vec;

        return intVec3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
    }

    inline intVec3 operator%(const intVec3& vec, int scalar)
    {
        return intVec3(vec.x % scalar, vec.y % scalar, vec.z % scalar);
    }


    inline bool operator==(const intVec3& a, const intVec3& b)
    {
        return a.x == b.x &&
               a.y == b.y &&
               a.z == b.z;
    }
    inline bool operator!=(const intVec3& a, const intVec3& b)
    {
        return !(a == b);
    }

    inline bool operator<(const intVec3& a, const intVec3& b)
    {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    }
    inline bool operator>(const intVec3& a, const intVec3& b)
    {
        if (a.x != b.x) return a.x > b.x;
        if (a.y != b.y) return a.y > b.y;
        return a.z > b.z;
    }

    inline bool operator<=(const intVec3& a, const intVec3& b)
    {
        if (a.x != b.x) return a.x <= b.x;
        if (a.y != b.y) return a.y <= b.y;
        return a.z <= b.z;
    }
    inline bool operator>=(const intVec3& a, const intVec3& b)
    {
        if (a.x != b.x) return a.x >= b.x;
        if (a.y != b.y) return a.y >= b.y;
        return a.z >= b.z;
    }

    #pragma endregion  
}