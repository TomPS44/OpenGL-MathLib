#pragma once

#include <cmath>
#include <concepts>

#include "Math\MathInternal.hpp"
#include "Math\Concepts.hpp"

namespace math
{
    template<std::floating_point F>
    struct vec3;

    struct mat4;

    template<std::floating_point F>
    struct alignas(16) quat  
    {
    public:
        union 
        {
            struct { F w, x, y, z; };
            F data[4];
        };

    public:
        quat(F qw, const vec3<F>& xyz);
        quat(F qw, F qx, F qy, F qz) : w(qw), x(qx), y(qy), z(qz) {}

        template<std::floating_point f = F>
        static quat<f> identity() { return quat(static_cast<f>(1.0), static_cast<f>(0.0), static_cast<f>(0.0), static_cast<f>(0.0)); }
        
        template<std::floating_point type>
        vec3<type> XYZ() const { return vec3<type>(static_cast<type>(x), static_cast<type>(y), static_cast<type>(z)); }
        template<std::floating_point type>
        vec3<type> ZYX() const { return vec3<type>(static_cast<type>(z), static_cast<type>(y), static_cast<type>(x)); }

        F* operator[](int index)
        {
            index = clamp<int>(index, 0, 3);

            return &data[index];
        }

        quat& normalized()
        {
            double l = this->length<double>();

            F invLen = static_cast<F>(1.0) / l;

            w *= invLen;
            x *= invLen;
            y *= invLen;
            z *= invLen;

            return *this;
        }
        template<std::floating_point type>
        quat<type> getUnitQuat() const
        {
            quat copy = *this;

            copy = copy.normalized();

            quat<type> unitCopy = quat<type>(static_cast<type>(w),
                                         static_cast<type>(x),
                                         static_cast<type>(y),
                                         static_cast<type>(z));

            return unitCopy;
        }

        quat& conjugated()
        {
            x *= static_cast<F>(-1.0);
            y *= static_cast<F>(-1.0);
            z *= static_cast<F>(-1.0);

            return *this;
        }
        template<std::floating_point type>
        quat<type> getConjugatedQuat() const
        {
            quat copy = *this;

            copy = copy.conjugated();

            quat<type> conjCopy = quat<type>(static_cast<type>(w),
                                         static_cast<type>(x),
                                         static_cast<type>(y),
                                         static_cast<type>(z));

            return conjCopy;
        }

        template<Number N>
        N length() const 
        {
            return static_cast<N>(std::sqrtf( (w * w) + (x * x) + (y * y) + (z * z) ));
        }

        template<Number N>
        static N length(const quat& quat)
        {
            return static_cast<N>(std::sqrtf( (quat.w * quat.w) + (quat.x * quat.x) + (quat.y * quat.y) + (quat.z * quat.z) ));
        }

        static quat fromAxisAngle(vec3<F> axis, F angle);

        static quat fromEuler(const vec3<F>& rotation);

        template<std::floating_point type>
        static vec3<type> rotatePointViaQuat(const vec3<F>& point, const quat<F>& rot)
        {
            
            quat qPoint = quat(static_cast<F>(0.0), point.XYZ());
            
            vec3 rotated = (rot * qPoint * rot.getConjugatedQuat<type>()).XYZ();

            return rotated;
        }

        vec3<F> toEuler() const;

        mat4 toMat4() const;
    };

    template<std::floating_point F>
    inline quat<F> operator*(const quat<F>& a, const quat<F>& b);
}