#pragma once

#include "Math\Concepts.hpp"

namespace glMath
{
    template<IntegralNumber I>
    struct iVec2;

    /*
    * @brief A struct used to store a 2D vector, with x and y components.
    *
    * You can access the different values via :
    * ```cpp
    * float xPos = vec.x;
    * float yPos = vec.data[1];
    * ```
    * 
    * @tparam F The type of the values of the vector. Either a float or a double. 
    */
    template<FloatingNumber F>
    struct vec2
    {
    public:
        union 
        {
            struct { F x, y; };
            F data[2];
        };

    public:

        /*
        * @brief Creates a vec2 with ``x`` and ``y`` being ``0``.
        * ```cpp
        * std::cout << vec2<float>().x; // 0
        * ```
        */ 
        inline constexpr vec2() noexcept;
        /*
        * @brief Creates a vec2 with ``x`` being equal to ``vx``, and ``y`` being equal to ``vy``.
        * ```cpp
        * std::cout << vec2<float>(2.0f, 3.0f).y; // 3
        * ```
        */ 
        inline constexpr vec2(F vx, F vy) noexcept;
        /*
        * @brief Creates a vec2 with ``x`` being equal to ``vec.x``, and ``y`` being equal to ``vec.y``. 
        * ```cpp
        * vec2<float> pos(4.4f, 3.3f);
        * vec2<float> pos2 = pos;
        * std::cout << pos.y; // 3.3
        * ```
        */ 
        inline constexpr vec2(const vec2<F>& vec) noexcept;
        /*
        * @brief Creates a vec2 from an angle, rotating anti-clockwise.
        * @param angleInDeg The angle in DEGREES.
        * ```cpp
        * vec2<float> pos = vec2<float>::fromAngle(90.0f);
        * std::cout << pos.y; // 1
        * ```
        */
        inline static vec2<F> fromAngle(F angleInDeg) noexcept;
        /**
        * @brief Returns a number as the type of the vec2, corresponding to the angle between ``a`` and ``b``.
        * @attention The angle returned is in RADIANS.
        * @param a The first vector.
        * @param b The second vector.
        * ```cpp
        * vec2<float> a(0.0f, 1.0f);
        * vec2<float> b(1.0f, 0.0f);
        * std::cout << vec2<float>::angleBetween(a, b); // 1.5708
        * ```
        */
        inline static F angleBetween(const vec2<F>& a, const vec2<F>& b) noexcept;

        
        /*
        * @brief Creates a vec2 with ``x`` and ``y`` being ``0``.
        * ```cpp
        * vec2<float> pos = vec2<float>::zero();
        * std::cout << pos.x; // 0
        * ```
        */
        inline static constexpr vec2 zero() noexcept { return vec2(0.0, 0.0); };
        /*
        * @brief Creates a vec2 with ``x`` and ``y`` being ``1``.
        * ```cpp
        * vec2<float> pos = vec2<float>::one();
        * std::cout << pos.y; // 1
        * ```
        */
        inline static constexpr vec2 one() noexcept  { return vec2(1.0, 1.0); };
        /*
        * @brief Creates a vec2 with ``x`` being ``-1`` and ``y`` being ``0``.
        * ```cpp
        * vec2<float> pos = vec2<float>::left();
        * std::cout << pos.x; // -1
        * ```
        */
        inline static constexpr vec2 left() noexcept { return vec2(-1.0, 0.0); };
        /*
        * @brief Creates a vec2 with ``x`` being ``1`` and ``y`` being ``0``.
        * ```cpp
        * vec2<float> pos = vec2<float>::right;
        * std::cout << pos.x; // 1
        * ```
        */
        inline static constexpr vec2 right() noexcept { return vec2(1.0, 0.0); };
        /*
        * @brief Creates a vec2 with ``x`` being ``0`` and ``y`` being ``1``.
        * ```cpp
        * vec2<float> pos = vec2<float>::up();
        * std::cout << pos.y; // 1
        * ```
        */
        inline static constexpr vec2 up() noexcept   { return vec2(0.0, 1.0); };
        /*
        * @brief Creates a vec2 with ``x`` being ``0`` and ``y`` being ``-1``.
        * ```cpp
        * vec2<float> pos = vec2<float>::down();
        * std::cout << pos.y; // -1
        * ```
        */
        inline static constexpr vec2 down() noexcept { return vec2(0.0, -1.0); };


        /*
        * @brief Returns a new vec2, with a different type but the same values, casted to the type.
        * @attention You might lose precision. 
        * 
        * If one value exceed the numerical limit of the new type, its clamped to the limit.
        *
        * ```cpp
        * vec2<float> vecf(3.2f, 2.1f);
        * vec2<double> vecd = vecf.as<double>();
        * std::cout << vecd.y; // 2.1
        * ```
        *
        * @tparam f The type of the new vec2.
        */
        template<FloatingNumber f>
        inline vec2<f> as() const noexcept;

        /*
        * @brief Returns an iVec2 of the same type of the vec2. Its values are floored to an integral number.
        *
        * ```cpp
        * vec2<float> vecf(-1.1f, 2.2f);
        * iVec2<int> veci = vecf.floorTo<int>();
        * std::cout << veci.x; // -2
        * std::cout << veci.y; // 2
        * ```
        */
        template<IntegralNumber type>
        inline iVec2<type> floorTo() const noexcept;
        /*
        * @brief Returns an iVec2 of the same type of the vec2. Its values are ceiled to an integral number.
        *
        * ```cpp
        * vec2<float> vecf(-1.1f, 2.2f);
        * iVec2<int> veci = vecf.ceilTo<int>();
        * std::cout << veci.x; // -1
        * std::cout << veci.y; // 3
        * ```
        */
        template<IntegralNumber type>
        inline iVec2<type> ceilTo() const noexcept;
        /*
        * @brief Returns an iVec2 of the same type of the vec2. Its values are rounded to an integral number.
        *
        * ```cpp
        * vec2<float> vecf(-1.1f, 2.2f);
        * iVec2<int> veci = vecf.roundTo<int>();
        * std::cout << veci.x; // -1
        * std::cout << veci.y; // 2
        * ```
        */
        template<IntegralNumber type>
        inline iVec2<type> roundTo() const noexcept;


        /**
        * @brief Returns a new vec2 of the same type, made from the y and x components.
        *
        * ```cpp
        * vec2<float> vec(1.0f, 4.0f);
        * vec2<float> nwVec = vec.yx();
        * std::cout << newVec.x; / 4
        * ```
        */
        inline constexpr vec2 yx() const noexcept { return vec2(y, x); };
        /**
        * @brief Returns a new vec2 of the same type, made from the x and x components.
        *
        * ```cpp
        * vec2<float> vec(1.0f, 4.0f);
        * vec2<float> nwVec = vec.xx();
        * std::cout << newVec.x; / 1
        * ```
        */
        inline constexpr vec2 xx() const noexcept { return vec2(x, x); };
        /**
        * @brief Returns a new vec2 of the same type, made from the y and y components.
        *
        * ```cpp
        * vec2<float> vec(1.0f, 4.0f);
        * vec2<float> nwVec = vec.yy();
        * std::cout << newVec.x; / 4
        * ```
        */
        inline constexpr vec2 yy() const noexcept { return vec2(y, y); };


        /**
         * @brief Returns a reference to the vec2. Its components are changed for its ``length`` to equal to ``1``.
         * @attention If its ``length`` is ``0``, it returns the vector unmodified.
         * 
         * ```cpp
         * vec2<float> dir(2.0f, 1.0f);
         * dir = dir.normalize();
         * std::cout << dir.x; // 0.894
         * std::cout << dir.y; // 0.447
         * ```
         */
        inline vec2& normalize() noexcept;
        /**
         * @brief Returns a new vec2 of the same type. Its components are changed for its ``length`` to equal to ``1``.
         * @attention If its ``length`` is ``0``, it returns the vector unmodified.
         * 
         * ```cpp
         * vec2<float> dir(2.0f, 1.0f);
         * vec2<float> normDir = dir.getNormalizedVec();
         * std::cout << normDir.x; // 0.894
         * std::cout << normDir.y; // 0.447
         * ```
         */
        inline vec2 getNormalizedVec() const noexcept;
        /**
         * @brief Returns a reference to the vec2. Its components are changed for its ``length`` to equal to ``1``.
         * @attention If its ``length`` is ``0``, it returns the vector unmodified.
         * 
         * ```cpp
         * vec2<float> dir(2.0f, 1.0f);
         * vec2<float> normdir = vec2<float>::normalized(dir);
         * std::cout << normDir.x; // 0.894
         * std::cout << normDir.y; // 0.447
         * ```
         */
        inline static vec2 normalized(const vec2& vec) noexcept;
        

        /**
         * @brief Returns a number as the type of the vec2, corresponding to the length of the vector.
         * 
         * ```cpp
         * vec2<float> vec(3.0f, 4.0f);
         * std::cout << vec.length(); // 5
         * ```
         */
        inline F length() const noexcept;
        /**
         * @brief Returns a number as the type of the vec2, corresponding to the squared length of the vector.
         * 
         * ```cpp
         * vec2<float> vec(3.0f, 4.0f);
         * std::cout << vec.lengthSquared(); // 25
         * ```
         */
        inline constexpr F lengthSquared() const noexcept;
        /**
         * @brief Returns a number as the type of the vec2, corresponding to the dot prodct of the vector with the one in the parameter.
         * @param other The other vector used to calculate the dot product. It needs to be the same type as the base vec2.
         * 
         * 
         */
        inline constexpr F dotProduct(const vec2& other) const noexcept;
        inline constexpr F crossProduct(const vec2& other) const noexcept;
        // Returns the distance between the vector, and the one specified as a parameter
        inline F distance(const vec2& other) const noexcept;
        // Returns the distance between the vector, and the one specified as a parameter, but squared
        inline constexpr F distanceSquared(const vec2& other) const noexcept;

        inline constexpr vec2 projectOnto(const vec2& base) const noexcept;




        inline static F length(const vec2& vec) noexcept;   
        inline static constexpr F lengthSquared(const vec2& vec) noexcept;
        inline static constexpr F dotProduct(const vec2& vec1, const vec2& vec2) noexcept;
        inline static constexpr F crossProduct(const vec2& vec1, const vec2& vec2) noexcept;
        inline static F distance(const vec2& vec1, const vec2& vec2) noexcept;
        inline static constexpr F distanceSquared(const vec2& vec1, const vec2& vec2) noexcept;
        inline static constexpr vec2 project(const vec2& proj, const vec2& base) noexcept;

        inline constexpr vec2 min(const vec2& other) const noexcept;
        inline static constexpr vec2 min(const vec2& a, const vec2& b) noexcept;

        inline constexpr vec2 max(const vec2& other) const noexcept;
        inline static constexpr vec2 max(const vec2& a, const vec2& b) noexcept;

        inline static constexpr vec2 lerp(const vec2& start, const vec2& end, F t) noexcept;
        inline static constexpr vec2 lerpUnclamped(const vec2& start, const vec2& end, F t) noexcept;
        inline static constexpr vec2 slerp(const vec2& start, const vec2& end, F t) noexcept;
        inline static constexpr vec2 slerpUnclamped(const vec2& start, const vec2& end, F t) noexcept;
        
 
        inline constexpr vec2& operator+=(const vec2& other) noexcept;
        inline constexpr vec2& operator-=(const vec2& other) noexcept;
        inline constexpr vec2& operator*=(F scalar) noexcept;
        inline constexpr vec2& operator/=(F scalar) noexcept;

        inline constexpr vec2 operator-() const noexcept;


        inline const F* valuePtr() const noexcept;
    };

    template<FloatingNumber F>
    inline constexpr vec2<F> operator+(const vec2<F>& a, const vec2<F>& b) noexcept;
    template<FloatingNumber F>
    inline constexpr vec2<F> operator+(const vec2<F>& a, F scalar) noexcept;

    template<FloatingNumber F>
    inline constexpr vec2<F> operator-(const vec2<F>& a, const vec2<F>& b) noexcept;
    template<FloatingNumber F>
    inline constexpr vec2<F> operator-(const vec2<F>& a, F scalar) noexcept;

    template<FloatingNumber F>
    inline constexpr vec2<F> operator*(const vec2<F>& a, const vec2<F>& b) noexcept;
    template<FloatingNumber F>
    inline constexpr vec2<F> operator*(const vec2<F>& vec, F scalar) noexcept;
    template<FloatingNumber F>
    inline constexpr vec2<F> operator*(F scalar, const vec2<F>& vec) noexcept;

    template<FloatingNumber F>
    inline constexpr vec2<F> operator/(const vec2<F>& vec, F scalar) noexcept;

    template<FloatingNumber F>
    inline constexpr bool operator==(const vec2<F>& a, const vec2<F>& b) noexcept;
    template<FloatingNumber F>
    inline constexpr bool operator!=(const vec2<F>& a, const vec2<F>& b) noexcept;
}

#include "Math\Vectors\Vector2.inl"