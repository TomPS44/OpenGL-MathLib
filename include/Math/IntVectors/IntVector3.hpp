#pragma once

#include "Math\Concepts.hpp"

namespace glMath
{
    template<FloatingNumber F>
    struct vec3;

    template<IntegralNumber I>
    struct iVec2;

    struct /*alignas(8)*/ intVec3 
    {
    public:
        union 
        {
            struct { int x, y, z; };
            struct { int r, g, b; };
            int data[3];
        };

    public:
        intVec3();
        intVec3(int scalar);
        intVec3(int vx, int vy, int vz);
        intVec3(const intVec3& vec);



        inline static intVec3 zero()     { return intVec3(0, 0, 0); };
        inline static intVec3 one()      { return intVec3(1, 1, 1); };
        inline static intVec3 right()    { return intVec3(1, 0, 0); };
        inline static intVec3 left()     { return intVec3(-1, 0, 0); };
        inline static intVec3 up()       { return intVec3(0, 1, 0); };
        inline static intVec3 down()     { return intVec3(0, -1, 0); };
        inline static intVec3 forward()  { return intVec3(0, 0, 1); };
        inline static intVec3 backward() { return intVec3(0, 0, -1); };

        /*
        inline intVec2 XX() const { return intVec2(x, x); }; 
        inline intVec2 YY() const { return intVec2(y, y); };
        inline intVec2 ZZ() const { return intVec2(z, z); };
        inline intVec2 XY() const { return intVec2(x, y); };
        inline intVec2 XZ() const { return intVec2(x, z); };
        inline intVec2 YX() const { return intVec2(y, x); };
        inline intVec2 YZ() const { return intVec2(y, z); };
        inline intVec2 ZX() const { return intVec2(z, x); };
        inline intVec2 ZY() const { return intVec2(z, y); };
        */

        inline intVec3 XXX() const { return intVec3(x, x, x); };
        inline intVec3 YYY() const { return intVec3(y, y, y); };
        inline intVec3 ZZZ() const { return intVec3(z, z, z); };
        inline intVec3 ZYX() const { return intVec3(z, y, x); };


        // template<IntegralNumber type>
        // intVec3<type> as() const;


        int lengthSquared() const;
        static int lengthSquared(const intVec3& vec);

        int dotProduct(const intVec3& other) const;
        static int dotProduct(const intVec3& a, const intVec3& b);

        intVec3 crossProduct(const intVec3& other) const;
        static intVec3 crossProduct(const intVec3& a, const intVec3& b);

        int distanceSquared(const intVec3& other) const;
        static int distanceSquared(const intVec3& a, const intVec3& b);

        intVec3& clamp(int minInclusive, int maxInclusive);
        intVec3 getClampedVec(int minInclusive, int maxInclusive) const;
        static intVec3 clamp(const intVec3& vec, int minInclusive, int maxInclusive);

        intVec3 min(const intVec3& other) const;
        static intVec3 min(const intVec3& a, const intVec3& b);

        intVec3 max(const intVec3& other) const;
        static intVec3 max(const intVec3& a, const intVec3& b);

        intVec3& absValue();
        intVec3 getAbsValueVec() const;
        static intVec3 abs(const intVec3& vec);

        template<FloatingNumber F>
        static intVec3 floor(const vec3<F>& fVec);
        template<FloatingNumber F>
        static intVec3 round(const vec3<F>& fVec);
        template<FloatingNumber F>
        static intVec3 toInt(const vec3<F>& fVec);



        intVec3& operator+=(const intVec3& other);
        intVec3& operator+=(int scalar);

        intVec3& operator-=(const intVec3& other);
        intVec3& operator-=(int scalar);

        intVec3& operator*=(int scalar);
        intVec3& operator*=(const intVec3& other);

        intVec3& operator/=(int scalar);

        intVec3& operator%=(int scalar);


        intVec3 operator-() const;

        const int* valuePtr() const;
        int& operator[](int index);
    };

    intVec3 operator+(const intVec3& a, const intVec3& b);
    intVec3 operator+(const intVec3& vec, int scalar);

    intVec3 operator-(const intVec3& a, const intVec3& b);
    intVec3 operator-(const intVec3& vec, int scalar);

    intVec3 operator*(const intVec3& a, const intVec3& b);
    intVec3 operator*(const intVec3& vec, int scalar);
    intVec3 operator*(int scalar, const intVec3& vec);

    intVec3 operator/(const intVec3& vec, int scalar);

    intVec3 operator%(const intVec3& vec, int scalar);


    bool operator==(const intVec3& a, const intVec3& b);
    bool operator!=(const intVec3& a, const intVec3& b);

    bool operator<(const intVec3& a, const intVec3& b);
    bool operator>(const intVec3& a, const intVec3& b);
    bool operator<=(const intVec3& a, const intVec3& b);
    bool operator>=(const intVec3& a, const intVec3& b);
}

template<>
struct std::hash<glMath::intVec3>
{
    size_t operator()(const glMath::intVec3& vec) const
    {
        // size_t h = 0;

        // h ^= hash<int>{}(vec.x) + 0x9e3779b9 + (h << 6) + (h >> 2);
        // h ^= hash<int>{}(vec.y) + 0x9e3779b9 + (h << 6) + (h >> 2);
        // h ^= hash<int>{}(vec.z) + 0x9e3779b9 + (h << 6) + (h >> 2);

        // return h;



        size_t h = 0;

        auto hash_combine = [&](int val) 
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