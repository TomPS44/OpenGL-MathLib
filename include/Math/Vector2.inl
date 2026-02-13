#include <concepts>
#include <cmath>


namespace math
{

    #pragma region Constructors

    template<std::floating_point F>
    inline vec2<F>::vec2()
    {
        x = static_cast<F>(0.0);
        y = static_cast<F>(0.0);
    }

    template <std::floating_point F>
    inline vec2<F>::vec2(F vx, F vy)
    {
        x = static_cast<F>(vx);
        y = static_cast<F>(vy);
    }

    template<std::floating_point F>
    inline vec2<F>::vec2(const vec2<F>& vec)
    {
        x = static_cast<F>(vec.x);
        y = static_cast<F>(vec.y);
    }

    #pragma endregion Constructors

    #pragma region StaticConstructors

    template <std::floating_point F>
    inline vec2 <F> vec2 <F> ::fromAngle(F angleInDeg)
    {
        return vec2(std::cosf(angleInDeg * math::degToRad<F>()), std::sinf(angleInDeg * math::degToRad<F>()));
    }
    
    template <std::floating_point F>
    inline vec2<F> vec2<F>::zero()
    {
        return vec2<F>(static_cast<F>(0.0), static_cast<F>(0.0));
    }
    template <std::floating_point F>
    inline vec2<F> vec2<F>::one()
    {
        return vec2<F>(static_cast<F>(1.0), static_cast<F>(1.0));
    }
    template <std::floating_point F>
    inline vec2<F> vec2<F>::up()
    {
        return vec2<F>(static_cast<F>(0.0), static_cast<F>(1.0));
    }
    template <std::floating_point F>
    inline vec2<F> vec2<F>::down()
    {
        return vec2<F>(static_cast<F>(0.0), static_cast<F>(-1.0));
    }
    template <std::floating_point F>
    inline vec2<F> vec2<F>::left()
    {
        return vec2<F>(static_cast<F>(-1.0), static_cast<F>(0.0));
    }
    template <std::floating_point F>
    inline vec2<F> vec2<F>::right()
    {
        return vec2<F>(static_cast<F>(1.0), static_cast<F>(0.0));
    }
    
    #pragma endregion StaticConstructors

    #pragma region Casting

    template<std::floating_point F>
    template<std::floating_point f>
    inline f vec2<F>::X() const
    {
        return static_cast<f>(x);
    } 

    template<std::floating_point F>
    template<std::floating_point f>
    inline f vec2<F>::Y() const
    {
        return static_cast<f>(y);
    } 


    template<std::floating_point F>
    template<std::floating_point f>
    inline vec2<f> vec2<F>::XX() const
    {
        return vec2<f>(static_cast<f>(x), static_cast<f>(x));
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec2<f> vec2<F>::YY() const
    {
        return vec2<f>(static_cast<f>(y), static_cast<f>(y));
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec2<f> vec2<F>::XY() const
    {
        return vec2<f>(static_cast<f>(x), static_cast<f>(y));
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec2<f> vec2<F>::YX() const
    {
        return vec2<f>(static_cast<f>(y), static_cast<f>(x));
    }

    #pragma endregion Casting

    #pragma region Normalizing

    template<std::floating_point F>
    inline vec2<F>& vec2<F>::normalized()
    {
        F l = this->length<F>();
        
        if (l > static_cast<F>(0.0)) 
        {
            F inverseLength = static_cast<F>(1.0) / l;
            x *= inverseLength; 
            y *= inverseLength;
        }

        return *this;
    }

    template<std::floating_point F>
    template<std::floating_point f>
    inline vec2<f> vec2<F>::getUnitVector() const
    {
        vec2 copy = *this;
        copy = copy.normalized();

        copy.x = static_cast<f>(copy.x);
        copy.y = static_cast<f>(copy.y);

        return copy;
    }

    #pragma endregion Normalizing

    #pragma region MemberMethods

    template<std::floating_point F>
    template<Number N>
    inline N vec2<F>::length() const
    {
        return static_cast<N>(std::sqrtf( (x * x) + (y * y) ));
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec2<F>::lengthSquared() const
    {
        return static_cast<N>( (x * x) + (y * y) );
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec2<F>::dotProduct(const vec2& other) const
    {
        return static_cast<N>(std::sqrtf( (other.x - x) * (other.x - x)  +  (other.y - y) * (other.y - y) ));
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec2<F>::distance(const vec2& other) const
    {
        return static_cast<N>(std::sqrtf( (other.x - x) * (other.x - x)  +  (other.y - y) * (other.y - y) ));
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec2<F>::distanceSquared(const vec2& other) const
    {
        return static_cast<N>((other.x - x) * (other.x - x)  +  (other.y - y) * (other.y - y) );
    }

    #pragma endregion MemberMethods

    #pragma region StaticMethods

    template<std::floating_point F>
    template<Number N>
    inline N vec2<F>::angleBetween(const vec2<F>& a, const vec2<F>& b)
    {
        F dot = math::clamp( static_cast<F>(vec2<F>::dotProduct(a.getUnitVector(), b.getUnitVector()), static_cast<F>(-1.0), static_cast<F>(1.0)) );

        return static_cast<F>(std::acos(dot));
    }


    template<std::floating_point F>
    template<Number N>
    inline N vec2<F>::length(const vec2<F>& vec) 
    {
        return static_cast<N>(std::sqrtf( (vec.x * vec.x) + (vec.y * vec.y) ));
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec2<F>::lengthSquared(const vec2& vec) 
    {
        return static_cast<N>( (vec.x * vec.x) + (vec.y * vec.y) );
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec2<F>::dotProduct(const vec2& a, const vec2& b)
    {
        return (a.x * b.x) + (a.y * b.y);
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec2<F>::distance(const vec2& a, const vec2& b) 
    {
        return static_cast<N>(std::sqrtf( (b.x - a.x) * (b.x - a.x)  +  (b.y - a.y) * (b.y - a.y) ));
    }

    template<std::floating_point F>
    template<Number N>
    inline N vec2<F>::distanceSquared(const vec2& a, const vec2& b) 
    {
        return static_cast<N>( (b.x - a.x) * (b.x - a.x)  +  (b.y - a.y) * (b.y - a.y) );
    }

    template<std::floating_point F>
    inline vec2<F> vec2<F>::lerp(const vec2<F>& start, const vec2<F>& end, F t)
    {
        t = clamp01(t);
        return vec2<F>( start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t );
    }

    template<std::floating_point F>
    inline vec2<F> vec2<F>::lerpUnclamped(const vec2<F>& start, const vec2<F>& end, F t)
    {
        return vec2<F>(start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t);
    }


    #pragma endregion StaticMethods

    #pragma region ReferenceOperators

    template<std::floating_point F>
    vec2<F>& vec2<F>::operator+=(const vec2<F>& other)
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }

    template<std::floating_point F>
    vec2<F>& vec2<F>::operator-=(const vec2<F>& other)
    {
        this->x -= other.x;
        this->y -= other.y;

        return *this;
    }

    template<std::floating_point F>
    vec2<F>& vec2<F>::operator*=(F scalar)
    {
        this->x *= scalar;
        this->y *= scalar;

        return *this;
    }


    template<std::floating_point F>
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

    template<std::floating_point F>
    const F* vec2<F>::valuePtr() const
    {
        return &data[0];
    }

    #pragma endregion ReferenceOperators

    #pragma region ArithmeticOperators

    template<std::floating_point F>
    inline vec2<F> operator+(const vec2<F>& a, const vec2<F>& b)
    {
        return vec2(a.x + b.x, a.y + b.y);
    }

    template<std::floating_point F>
    inline vec2<F> operator-(const vec2<F>& a, const vec2<F>& b)
    {
        return vec2(a.x - b.x, a.y - b.y);
    }

    template<std::floating_point F>
    inline vec2<F> operator*(const vec2<F>& vec, F scalar)
    {
        return vec2(vec.x * scalar, vec.y * scalar);
    }
    template<std::floating_point F>
    inline vec2<F> operator*(F scalar, const vec2<F>& vec)
    {
        return vec2(vec.x * scalar, vec.y * scalar);
    }

    template<std::floating_point F>
    inline vec2<F> operator/(const vec2<F>& vec, F scalar)
    {
        if (scalar == static_cast<F>(0.0)) return vec;

        scalar = static_cast<F>(1.0) / scalar;

        return vec2(vec.x / scalar, vec.y / scalar);
    }


    template<std::floating_point F>
    inline bool operator==(const vec2<F>& a, const vec2<F>& b)
    {
        return static_cast<F>( std::abs(b.x - a.x) ) < math::epsilon<F>() &&
               static_cast<F>( std::abs(b.y - a.y) ) < math::epsilon<F>();
    }

    template<std::floating_point F>
    inline bool operator!=(const vec2<F>& a, const vec2<F>& b)
    {
        return !(a == b);
    }

    #pragma endregion ArithmeticOperators

}

