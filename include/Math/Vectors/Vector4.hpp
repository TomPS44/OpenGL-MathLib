#pragma once 

#include "Math\Concepts.hpp"

namespace glMath
{
    template<FloatingNumber F>
    struct vec3;

    // A struct used to represent a Vector4, with x, y, z and w components
    template<FloatingNumber F>
    struct alignas(sizeof(F) * 4) vec4
    {
    public:
        union 
        {
            struct { F x, y, z, w; };
            struct { F r, g, b, a; };
            struct { F s, t, p, q; };
            F data[4];
        };

    public:
         
        vec4();

        vec4(F scalar);
        
        vec4(F vx, F vy, F vz, F vw);
         
        vec4(const vec4& vec);
        
        vec4(const vec3<F>& xyz, F vw);


        inline static vec4<F> directionZero()     { return vec4(0.0, 0.0, 0.0, 0.0); };    
        inline static vec4<F> directionOne()      { return vec4(1.0, 1.0, 1.0, 0.0); };   
        inline static vec4<F> directionRight()    { return vec4(1.0, 0.0, 0.0, 0.0); };    
        inline static vec4<F> directionLeft()     { return vec4(-1.0, 0.0, 0.0, 0.0); };  
        inline static vec4<F> directionUp()       { return vec4(0.0, 1.0, 0.0, 0.0); };   
        inline static vec4<F> directionDown()     { return vec4(0.0, -1.0, 0.0, 0.0); };  
        inline static vec4<F> directionForward()  { return vec4(0.0, 0.0, 1.0, 0.0); };   
        inline static vec4<F> directionBackward() { return vec4(0.0, 0.0, -1.0, 0.0); }; 

        inline static vec4<F> pointZero()     { return vec4(0.0, 0.0, 0.0, 1.0); };    
        inline static vec4<F> pointOne()      { return vec4(1.0, 1.0, 1.0, 1.0); };   
        inline static vec4<F> pointRight()    { return vec4(1.0, 0.0, 0.0, 1.0); };    
        inline static vec4<F> pointLeft()     { return vec4(-1.0, 0.0, 0.0, 1.0); };  
        inline static vec4<F> pointUp()       { return vec4(0.0, 1.0, 0.0, 1.0); };   
        inline static vec4<F> pointDown()     { return vec4(0.0, -1.0, 0.0, 1.0); };  
        inline static vec4<F> pointForward()  { return vec4(0.0, 0.0, 1.0, 1.0); };   
        inline static vec4<F> pointBackward() { return vec4(0.0, 0.0, -1.0, 1.0); };   
        
        
    
        inline vec4 wzyx() const { return vec4(w, z, y, x); }; 



        template<FloatingNumber type>
        vec4<type> as() const;
        

        vec3<F> toVec3() const;
        vec3<F> projectToVec3() const;
        static vec3<F> projectToVec3(const vec4& vec);


        const F* valuePtr() const;


        F length() const;
        F length3() const;
        F lengthSquared() const;
        F lengthSquared3() const;

        F dotProduct(const vec4& other) const;
        F dotProduct3(const vec4& other) const;

        F distance(const vec4& other) const;
        F distance3(const vec4& other) const;
        F distanceSquared(const vec4& other) const;
        F distanceSquared3(const vec4& other) const;

        static F length(const vec4& vec);
        static F length3(const vec4& vec);
        static F lengthSquared(const vec4& vec);
        static F lengthSquared3(const vec4& vec);

        static F dotProduct(const vec4& vec1, const vec4& vec2);
        static F dotProduct3(const vec4& vec1, const vec4& vec2);

        static F distance(const vec4& vec1, const vec4& vec2);
        static F distance3(const vec4& vec1, const vec4& vec2);
        static F distanceSquared(const vec4& vec1, const vec4& vec2);
        static F distanceSquared3(const vec4& vec1, const vec4& vec2);


        vec4 min(const vec4& other) const;
        static vec4 min(const vec4& a, const vec4& b);

        vec4 max(const vec4& other) const;
        static vec4 max(const vec4& a, const vec4& b);

        
        vec4& normalize();
        vec4& normalize3();
        vec4 getNormalizedVec() const;
        vec4 getNormalizedVec3() const;
        static vec4 normalized(const vec4& vec);
        static vec4 normalized3(const vec4& vec);


        static vec4 lerp(const vec4& start, const vec4& end, F t);
        static vec4 lerpUnclamped(const vec4& start, const vec4& end, F t);

        
        vec4& operator+=(const vec4& other);
        vec4& operator+=(F scalar);
        vec4& operator-=(const vec4& other);
        vec4& operator-=(F scalar);
        vec4& operator*=(const vec4<F>& other);
        vec4& operator*=(F scalar);
        vec4& operator/=(F scalar);

        vec4 operator-() const;
    };

    template<FloatingNumber F>
    inline vec4<F> operator+(const vec4<F>& a, const vec4<F>& b);
    template<FloatingNumber F>
    inline vec4<F> operator+(const vec4<F>& a, F scalar);

    template<FloatingNumber F>
    inline vec4<F> operator-(const vec4<F>& a, const vec4<F>& b);
    template<FloatingNumber F>
    inline vec4<F> operator-(const vec4<F>& a, F scalar);

    template<FloatingNumber F>
    inline vec4<F> operator*(const vec4<F>& a, const vec4<F>& b);
    template<FloatingNumber F>
    inline vec4<F> operator*(const vec4<F>& vec, F scalar);
    template<FloatingNumber F>
    inline vec4<F> operator*(F scalar, const vec4<F>& vec);
    template<FloatingNumber F>
    inline vec4<F> operator/(const vec4<F>& vec, F scalar);

    template<FloatingNumber F>
    inline bool operator==(const vec4<F>& a, const vec4<F>& b);
    template<FloatingNumber F>
    inline bool operator!=(const vec4<F>& a, const vec4<F>& b);
}

#include "Math\Vectors\Vector4.inl"
