#pragma once

#include "Math\Concepts.hpp"

namespace glMath
{
    template<FloatingNumber F>
    struct vec3;

    template<IntegralNumber I>
    struct iVec2;

    /// @brief A struct to store 3 components x, y and z. They are the same type as I. 
    /// You can acces them via vec.x/y/z, vec.r/g/b, vec.data[(0-3)].
    /// @tparam I An IntegralNumber, so either an int, a long, or a long long. The components are stored as this type
    template<IntegralNumber I>
    struct iVec3
    {
    public:
        union 
        {
            struct { I x, y, z; };
            struct { I r, g, b; };
            I data[3];
        };

    public:
        iVec3();
        iVec3(I scalar);
        iVec3(I vx, I vy, I vz);
        iVec3(const iVec3<I>& vec);



        inline static iVec3<I> zero()     { return iVec3<I>(0, 0, 0); };
        inline static iVec3<I> one()      { return iVec3<I>(1, 1, 1); };
        inline static iVec3<I> right()    { return iVec3<I>(1, 0, 0); };
        inline static iVec3<I> left()     { return iVec3<I>(-1, 0, 0); };
        inline static iVec3<I> up()       { return iVec3<I>(0, 1, 0); };
        inline static iVec3<I> down()     { return iVec3<I>(0, -1, 0); };
        inline static iVec3<I> forward()  { return iVec3<I>(0, 0, 1); };
        inline static iVec3<I> backward() { return iVec3<I>(0, 0, -1); };

        
        inline iVec2<I> xx() const { return iVec2<I>(x, x); }; 
        inline iVec2<I> yy() const { return iVec2<I>(y, y); };
        inline iVec2<I> zz() const { return iVec2<I>(z, z); };
        inline iVec2<I> xy() const { return iVec2<I>(x, y); };
        inline iVec2<I> xz() const { return iVec2<I>(x, z); };
        inline iVec2<I> yx() const { return iVec2<I>(y, x); };
        inline iVec2<I> yz() const { return iVec2<I>(y, z); };
        inline iVec2<I> zx() const { return iVec2<I>(z, x); };
        inline iVec2<I> zy() const { return iVec2<I>(z, y); };
        

        inline iVec3<I> xxx() const { return iVec3<I>(x, x, x); };
        inline iVec3<I> yyy() const { return iVec3<I>(y, y, y); };
        inline iVec3<I> zzz() const { return iVec3<I>(z, z, z); };
        inline iVec3<I> zyx() const { return iVec3<I>(z, y, x); };


        template<IntegralNumber type>
        iVec3<type> as() const;

        template<FloatingNumber type>
        vec3<type> to() const;


        template<FloatingNumber F>
        F length() const;
        template<FloatingNumber F>
        static F length(const iVec3<I>& vec);

        /// @brief Calculates the Manhattan distance between itself and the vector in the parameter.
        /// @param other The second vector used to caculate the distance.
        /// @return The distance as the type of the iVecs.
        I iDistance(const iVec3<I>& other) const;
        static I iDistance(const iVec3<I>& a, const iVec3<I>& b);
        template<FloatingNumber F>
        /// @brief Calculates the Euclidean distance between itself and the vector in the parameter.
        /// @param other The second vector used to caculate the distance.
        /// @return The distance as the type of the iVecs.
        F distance(const iVec3<I>& other) const;
        template<FloatingNumber F>
        static F distance(const iVec3<I>& a, const iVec3<I>& b);

        I lengthSquared() const;
        static I lengthSquared(const iVec3<I>& vec);

        I dotProduct(const iVec3<I>& other) const;
        static I dotProduct(const iVec3<I>& a, const iVec3<I>& b);

        iVec3<I> crossProduct(const iVec3<I>& other) const;
        static iVec3<I> crossProduct(const iVec3<I>& a, const iVec3<I>& b);

        I distanceSquared(const iVec3<I>& other) const;
        static I distanceSquared(const iVec3<I>& a, const iVec3<I>& b);

        iVec3<I>& clamp(I minInclusive, I maxInclusive);
        iVec3<I> getClampedVec(I minInclusive, I maxInclusive) const;
        static iVec3<I> clamp(const iVec3<I>& vec, I minInclusive, I maxInclusive);

        iVec3<I> min(const iVec3<I>& other) const;
        static iVec3<I> min(const iVec3<I>& a, const iVec3<I>& b);

        iVec3<I> max(const iVec3<I>& other) const;
        static iVec3<I> max(const iVec3<I>& a, const iVec3<I>& b);

        iVec3<I>& absValue();
        iVec3<I> getAbsValueVec() const;
        static iVec3<I> abs(const iVec3<I>& vec);

        template<FloatingNumber F>
        static iVec3<I> floor(const vec3<F>& fVec);
        template<FloatingNumber F>
        static iVec3<I> ceil(const vec3<F>& fVec);
        template<FloatingNumber F>
        static iVec3<I> round(const vec3<F>& fVec);
        



        iVec3<I>& operator+=(const iVec3<I>& other);
        iVec3<I>& operator+=(I scalar);

        iVec3<I>& operator-=(const iVec3<I>& other);
        iVec3<I>& operator-=(I scalar);

        iVec3<I>& operator*=(I scalar);
        iVec3<I>& operator*=(const iVec3<I>& other);

        iVec3<I>& operator/=(I scalar);

        iVec3<I>& operator%=(I scalar);


        iVec3<I> operator-() const;

        const I* valuePtr() const;
    };

    template<IntegralNumber I>
    iVec3<I> operator+(const iVec3<I>& a, const iVec3<I>& b);
    template<IntegralNumber I>
    iVec3<I> operator+(const iVec3<I>& vec, I scalar);

    template<IntegralNumber I>
    iVec3<I> operator-(const iVec3<I>& a, const iVec3<I>& b);
    template<IntegralNumber I>
    iVec3<I> operator-(const iVec3<I>& vec, I scalar);

    template<IntegralNumber I>
    iVec3<I> operator*(const iVec3<I>& a, const iVec3<I>& b);
    template<IntegralNumber I>
    iVec3<I> operator*(const iVec3<I>& vec, I scalar);
    template<IntegralNumber I>
    iVec3<I> operator*(I scalar, const iVec3<I>& vec);

    template<IntegralNumber I>
    iVec3<I> operator/(const iVec3<I>& vec, I scalar);

    template<IntegralNumber I>
    iVec3<I> operator%(const iVec3<I>& vec, I scalar);


    template<IntegralNumber I>
    bool operator==(const iVec3<I>& a, const iVec3<I>& b);
    template<IntegralNumber I>
    bool operator!=(const iVec3<I>& a, const iVec3<I>& b);

    template<IntegralNumber I>
    bool operator<(const iVec3<I>& a, const iVec3<I>& b);
    template<IntegralNumber I>
    bool operator>(const iVec3<I>& a, const iVec3<I>& b);
    template<IntegralNumber I>
    bool operator<=(const iVec3<I>& a, const iVec3<I>& b);
    template<IntegralNumber I>
    bool operator>=(const iVec3<I>& a, const iVec3<I>& b);
}

template<glMath::IntegralNumber I>
struct std::hash<glMath::iVec3<I>>
{
    size_t operator()(const glMath::iVec3<I>& vec) const
    {
        // size_t h = 0;

        // h ^= hash<I>{}(vec.x) + 0x9e3779b9 + (h << 6) + (h >> 2);
        // h ^= hash<I>{}(vec.y) + 0x9e3779b9 + (h << 6) + (h >> 2);
        // h ^= hash<I>{}(vec.z) + 0x9e3779b9 + (h << 6) + (h >> 2);

        // return h;



        size_t h = 0;

        auto hash_combine = [&](I val) 
        {
            size_t k = static_cast<size_t>(val);
            k *= 0xcc9e2d51;
            k = (k << 15) | (k >> (sizeof(size_t) * 8 - 15));
            k *= 0x1b873593;
            h ^= k;
            h = (h << 13) | (h >> (sizeof(size_t) * 8 - 13));
            h = h * 5 + 0xe6546b64;
        };
        hash_combine(vec.x);
        hash_combine(vec.y);
        hash_combine(vec.z);

        // Finalizer
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;

        return h;
        
    }
};

#include "Math\IntVectors\IntVector3.inl"