#pragma once

#include "Math\Concepts.hpp"

namespace glMath
{
    template<FloatingNumber F>
    struct vec2;

    template<IntegralNumber I>
    struct alignas(sizeof(I) * 4) iVec2
    {
    public:
        union 
        {
            struct { I x, y; };
            I data[2];
        };

    public:
        iVec2();
        iVec2(I scalar);
        iVec2(I vx, I vy);
        iVec2(const iVec2<I>& vec);


        inline static iVec2<I> zero()  { return iVec2<I>(0, 0); }
        inline static iVec2<I> one()   { return iVec2<I>(1, 1); }
        inline static iVec2<I> right() { return iVec2<I>(1, 0); }
        inline static iVec2<I> left()  { return iVec2<I>(-1, 0); }
        inline static iVec2<I> down()  { return iVec2<I>(0, -1); }
        inline static iVec2<I> up()    { return iVec2<I>(0, 1); }


        inline iVec2<I> YX() const { return iVec2<I>(y, x); };
        inline iVec2<I> XX() const { return iVec2<I>(x, x); };
        inline iVec2<I> YY() const { return iVec2<I>(y, y); };


        template<IntegralNumber type>
        iVec2<type> as() const;


        I lengthSquared() const;
        static I lengthSquared(const iVec2<I>& vec);

        template<FloatingNumber F>
        F length() const;
        template<FloatingNumber F>
        static F length(const iVec2<I>& vec);

        I dotProduct(const iVec2<I>& other) const;
        static I dotProduct(const iVec2<I>& a, const iVec2<I>& b);

        I distanceSquared(const iVec2<I>& other) const;
        static I distanceSquared(const iVec2<I>& a, const iVec2<I>& b);

        iVec2<I>& clamp(I minInclusive, I maxInclusive);
        iVec2<I> getClampedVec(I minInclusive, I maxInclusive) const;
        static iVec2<I> clamp(const iVec2<I>& vec, I minInclusive, I maxInclusive);

        iVec2<I> min(const iVec2<I>& other) const;
        static iVec2<I> min(const iVec2<I>& a, const iVec2<I>& b);

        iVec2<I> max(const iVec2<I>& other) const;
        static iVec2<I> max(const iVec2<I>& a, const iVec2<I>& b);

        iVec2<I>& absValue();
        iVec2<I> getAbsValueVec() const;
        static iVec2<I> abs(const iVec2<I>& vec);

        template<FloatingNumber F>
        static iVec2<I> floor(const vec2<F>& fVec);
        template<FloatingNumber F>
        static iVec2<I> ceil(const vec2<F>& fVec);
        template<FloatingNumber F>
        static iVec2<I> round(const vec2<F>& fVec);


        iVec2<I>& operator+=(const iVec2<I>& other);
        iVec2<I>& operator+=(I scalar);

        iVec2<I>& operator-=(const iVec2<I>& other);
        iVec2<I>& operator-=(I scalar);

        iVec2<I>& operator*=(I scalar);
        iVec2<I>& operator*=(const iVec2<I>& other);

        iVec2<I>& operator/=(I scalar);

        iVec2<I>& operator%=(I scalar);


        iVec2<I> operator-() const;

        const I* valuePtr() const;
        I& operator[](I index);
    };


    template<IntegralNumber I>
    iVec2<I> operator+(const iVec2<I>& a, const iVec2<I>& b);
    template<IntegralNumber I>
    iVec2<I> operator+(const iVec2<I>& vec, I scalar);

    template<IntegralNumber I>
    iVec2<I> operator-(const iVec2<I>& a, const iVec2<I>& b);
    template<IntegralNumber I>
    iVec2<I> operator-(const iVec2<I>& vec, I scalar);

    template<IntegralNumber I>
    iVec2<I> operator*(const iVec2<I>& a, const iVec2<I>& b);
    template<IntegralNumber I>
    iVec2<I> operator*(const iVec2<I>& vec, I scalar);
    template<IntegralNumber I>
    iVec2<I> operator*(I scalar, const iVec2<I>& vec);

    template<IntegralNumber I>
    iVec2<I> operator/(const iVec2<I>& vec, I scalar);
    template<IntegralNumber I>
    iVec2<I> operator%(const iVec2<I>& vec, I scalar);

    template<IntegralNumber I>
    bool operator==(const iVec2<I>& a, const iVec2<I>& b);
    template<IntegralNumber I>
    bool operator!=(const iVec2<I>& a, const iVec2<I>& b);

    template<IntegralNumber I>
    bool operator<(const iVec2<I>& a, const iVec2<I>& b);
    template<IntegralNumber I>
    bool operator>(const iVec2<I>& a, const iVec2<I>& b);
    template<IntegralNumber I>
    bool operator<=(const iVec2<I>& a, const iVec2<I>& b);
    template<IntegralNumber I>
    bool operator>=(const iVec2<I>& a, const iVec2<I>& b);
}

template<IntegralNumber I>
struct std::hash<iVec2<I>>
{
    size_t operator()(const iVec2<I>& vec) const
    {
        // size_t hx = hash<I>{}(vec.x);
        // size_t hy = hash<I>{}(vec.y);

        // return hx ^ (hy + 0x9e3779b9 + (hx << 6) + (hx >> 2));

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

        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;

        return h;
    }
};

#include "Math\IntVectors\IntVector2.inl"