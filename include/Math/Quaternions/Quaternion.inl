#include <concepts>
#include <cmath>

#include "Math\MathInternal.hpp"

namespace math
{
    #pragma region Constructors

    template<FloatingNumber F>
    inline quat<F>::quat()
    {
        F f0 = static_cast<F>(0.0);

        w = f0;
        x = f0;
        y = f0;
        z = f0;
    }

    template<FloatingNumber F>
    inline quat<F>::quat(F qw, const vec3<F>& xyz)
    {
        w = qw;
        x = xyz.x;
        y = xyz.y;
        z = xyz.z;
    }

    template<FloatingNumber F>
    inline quat<F>::quat(F qw, F qx, F qy, F qz)
    {
        w = qw;
        x = qx;
        y = qy;
        z = qz;
    }

    #pragma endregion

    #pragma region StaticConstructors

    template<FloatingNumber F>
    inline quat<F> quat<F>::identity()
    {
        F f0 = static_cast<F>(0.0);

        return quat<F>(static_cast<F>(1.0), f0, f0, f0);
    }

    template<FloatingNumber F>
    inline quat<F> quat<F>::getPureQuat(const vec3<F>& vec)
    {
        return quat<F>(static_cast<F>(0.0), vec.x, vec.y, vec.z);
    }


    template<FloatingNumber F>
    inline quat<F> quat<F>::fromEuler(const vec3<F>& rotation)
    {
        return quat<F>::fromEuler(rotation.x, rotation.y, rotation.z);
    }

    template<FloatingNumber F>
    inline quat<F> quat<F>::fromEuler(F vx, F vy, F vz)
    {
        // return quat<F>::fromEuler( vec3<F>(vx, vy, vz) );

        F qx = (vx * math::degToRad<F>()) * static_cast<F>(0.5);
        F qy = (vy * math::degToRad<F>()) * static_cast<F>(0.5);
        F qz = (vz * math::degToRad<F>()) * static_cast<F>(0.5);

        F cx = std::cos(qx); F sx = std::sin(qx);
        F cy = std::cos(qy); F sy = std::sin(qy);
        F cz = std::cos(qz); F sz = std::sin(qz);

        

        // Bon, voilà la formule : (pour l'ordre ZYX)
        
        // w = cos(phi / 2) * cos(theta / 2) * cos(psy / 2) + sin(phi / 2) * sin(theta / 2) * sin(psy / 2) 
        // x = sin(phi / 2) * cos(theta / 2) * cos(psy / 2) - cos(phi / 2) * sin(theta / 2) * sin(psy / 2) 
        // y = cos(phi / 2) * sin(theta / 2) * cos(psy / 2) + sin(phi / 2) * cos(theta / 2) * sin(psy / 2) 
        // z = cos(phi / 2) * cos(theta / 2) * sin(psy / 2) - sin(phi / 2) * sin(theta / 2) * cos(psy / 2) 

        // Mais pour je ne sais quelle raison, avec l'ordre YXZ, ça devient + + - - au lieu de + - +
        
        return quat<F>(
            // cx * cy * cz + sx * sy * sz, 
            // sx * cy * cz + cx * sy * sz, 
            // cx * sy * cz - sx * cy * sz, 
            // cx * cy * sz - sx * sy * cz  
            cx * cy * cz + sx * sy * sz, 
            sx * cy * cz + cx * sy * sz, 
            cx * sy * cz - sx * cy * sz, 
            cx * cy * sz - sx * sy * cz  
        );
    }

    #pragma endregion

    #pragma region Casting

    template<FloatingNumber F>
    inline vec3<F> quat<F>::XYZ() const
    {
        return vec3<F>(x, y, z);
    }

    template<FloatingNumber F>
    inline vec3<F> quat<F>::ZYX() const
    {
        return vec3<F>(z, y, x);
    }

    template<FloatingNumber F>
    template<FloatingNumber f>
    inline quat<f> quat<F>::as() const
    {
        return quat<f>(static_cast<f>(w), static_cast<f>(x), static_cast<f>(y), static_cast<f>(z));
    }


    #pragma endregion

    #pragma region Normalizing

    template<FloatingNumber F>
    inline quat<F>& quat<F>::normalized()   
    {
        F l = this->length<F>();

        if (std::abs(l) > math::epsilon<F>()) 
        {
            F invLen = static_cast<F>(1.0) / l;
    
            w *= invLen;
            x *= invLen;
            y *= invLen;
            z *= invLen;
        }

        return *this;
    }
 
    template<FloatingNumber F>
    inline quat<F> quat<F>::getUnitQuat() const
    {
        quat copy = *this;

        return copy.normalized();
    }


    template<FloatingNumber F>
    inline quat<F>& quat<F>::conjugated()
    {
        x *= static_cast<F>(-1.0);
        y *= static_cast<F>(-1.0);
        z *= static_cast<F>(-1.0);

        return *this;
    }

    template<FloatingNumber F>
    inline quat<F> quat<F>::getConjugatedQuat() const
    {
        quat copy = *this;

        return copy.conjugated();
    }


    template<FloatingNumber F>
    inline quat<F>& quat<F>::inversed()
    {
        quat<F> conj = this->getConjugatedQuat();
        F l = this->lengthSquared();

        if (l > math::epsilon<F>())
        {
            w = conj.w / l;
            x = conj.x / l; 
            y = conj.y / l; 
            z = conj.z / l; 
        }

        return *this;
    }

    template<FloatingNumber F>
    inline quat<F> quat<F>::getInversedQuat() const
    {
        quat copy = *this;

        return copy.inversed();
    }

    #pragma endregion

    #pragma region MemberMethods

    template<FloatingNumber F>
    inline F* quat<F>::valuePtr() const
    {
        return &data[0];
    }


    template<FloatingNumber F>
    template<Number N>
    inline N quat<F>::length() const 
    {
        return static_cast<N>(std::sqrt( (w * w) + (x * x) + (y * y) + (z * z) ));
    }

    template<FloatingNumber F>
    template<Number N>
    inline N quat<F>::lengthSquared() const 
    {
        return static_cast<N>( (w * w) + (x * x) + (y * y) + (z * z) );
    }

    
    template<FloatingNumber F>
    template<Number N>
    inline N quat<F>::dotProduct(const quat<F>& other) const
    {
        return static_cast<N>( (w * other.w) + (x * other.x) + (y * other.y) + (z * other.z) );
    }



    template<FloatingNumber F>
    inline mat3<F> quat<F>::toMat3() const 
    {
        F xx = x * x;
        F yy = y * y;
        F zz = z * z;
        F xy = x * y;
        F wz = w * z;
        F wy = w * y;
        F wx = w * x;
        F xz = x * z;
        F yz = y * z;

        F f0 = static_cast<F>(0.0);

        return mat3<F>(1 - 2 * (yy + zz), 2 * (xy - wz)    , 2 * (xz + wy),
                       2 * (xy + wz)    , 1 - 2 * (xx + zz), 2 * (yz - wx),
                       2 * (xz - wy)    , 2 * (yz + wx)    , 1 - 2 * (xx + yy));
    }

    template<FloatingNumber F>
    inline mat4<F> quat<F>::toMat4() const 
    {
        F xx = x * x;
        F yy = y * y;
        F zz = z * z;
        F xy = x * y;
        F wz = w * z;
        F wy = w * y;
        F wx = w * x;
        F xz = x * z;
        F yz = y * z;

        F f0 = static_cast<F>(0.0);

        return mat4<F>(1 - 2 * (yy + zz), 2 * (xy - wz)    , 2 * (xz + wy)    , f0,
                       2 * (xy + wz)    , 1 - 2 * (xx + zz), 2 * (yz - wx)    , f0,
                       2 * (xz - wy)    , 2 * (yz + wx)    , 1 - 2 * (xx + yy), f0,
                       f0               , f0               , f0               , static_cast<F>(1.0));
    }


    template<FloatingNumber F>
    inline vec3<F> quat<F>::toEuler() const
    {
        vec3<F> angles;

        F sinX = static_cast<F>(2.0) * (w * x - y * z);
        
        if (std::abs(sinX) >= static_cast<F>(0.99999)) 
        {
            angles.x = std::copysign(math::pi<F>() / static_cast<F>(2.0), sinX);
            angles.y = static_cast<F>(2.0) * std::atan2(y, w);
            angles.z = static_cast<F>(0.0);
        } 
        else 
        {
            angles.x = std::asin(sinX);
            angles.y = std::atan2(static_cast<F>(2.0) * (w * y + z * x), static_cast<F>(1.0) - static_cast<F>(2.0) * (x * x + y * y));
            angles.z = std::atan2(static_cast<F>(2.0) * (w * z + x * y), static_cast<F>(1.0) - static_cast<F>(2.0) * (z * z + x * x));
        }

        angles.x *= math::radToDeg<F>();
        angles.y *= math::radToDeg<F>();
        angles.z *= math::radToDeg<F>();

        return angles;
    }

    #pragma endregion

    #pragma region StaticMethods
    
    template<FloatingNumber F>
    template<Number N>
    inline N quat<F>::length(const quat<F>& quat)  
    {
        return static_cast<N>(std::sqrt( (quat.w * quat.w) + (quat.x * quat.x) + (quat.y * quat.y) + (quat.z * quat.z) ));
    }

    template<FloatingNumber F>
    template<Number N>
    inline N quat<F>::lengthSquared(const quat<F>& quat)  
    {
        return static_cast<N>( (quat.w * quat.w) + (quat.x * quat.x) + (quat.y * quat.y) + (quat.z * quat.z) );
    }


    template<FloatingNumber F>
    template<Number N>
    inline N quat<F>::dotProduct(const quat<F>& a, const quat<F>& b)  
    {
        return static_cast<N>( (a.w * b.w) + (a.x * b.x) + (a.y * b.y) + (a.z * b.z) );
    }

    template<FloatingNumber F>
    inline quat<F> quat<F>::fromAxisAngle(const vec3<F> axis, F angle)
    {
        vec3<F> rotAxis = axis.getUnitVector();
        F theta = (angle * math::degToRad<F>()) / static_cast<F>(2.0);

        F cosTheta = static_cast<F>(std::cos(theta));
        F sinTheta = static_cast<F>(std::sin(theta));

        F w = cosTheta;
        F x = rotAxis.x * sinTheta;
        F y = rotAxis.y * sinTheta;
        F z = rotAxis.z * sinTheta;

        return quat(w, x, y, z);
    }

    template<FloatingNumber F>
    inline quat<F> quat<F>::lookAtFree(const vec3<F>& eye, const vec3<F>& target)
    {
        F f0 = static_cast<F>(0.0);
        F f1 = static_cast<F>(1.0);

        vec3<F> forward = (target - eye).getUnitVector();

        vec3<F> localForward = vec3<F>(f0, f0, f1);

        F dot = vec3<F>::dotProduct(localForward, forward);
        
        if (std::abs(dot + static_cast<F>(1.0)) < math::epsilon<F>())
        {
            vec3<F> axis = vec3<F>::crossProduct(vec3<F>(f1, f0, f0), localForward);
        
            if (axis.lengthSquared() < math::epsilon<F>())
            {
                axis = vec3<F>::crossProduct(vec3<F>(f0, f1, f0), localForward);
            }

            axis = axis.getUnitVector();

            return quat<F>(static_cast<F>(0.0), axis.x, axis.y, axis.z);
        }

        if (std::abs(dot - static_cast<F>(1.0)) < math::epsilon<F>())
        {
            return quat<F>::identity();
        }

        vec3<F> axis = vec3<F>::crossProduct(localForward, forward);

        F s = std::sqrt( (f1 + dot) * static_cast<F>(2.0) );

        F invS = static_cast<F>(1.0) / s;


        return quat<F>(s * static_cast<F>(0.5), axis.x * invS, axis.y * invS, axis.z * invS).normalized();
    }

    template<FloatingNumber F>
    inline quat<F> quat<F>::lookAt(const vec3<F>& eye, const vec3<F>& target, const vec3<F>& up)
    {
        F f0 = static_cast<F>(0.0);
        F f1 = static_cast<F>(1.0);
        F f2 = static_cast<F>(2.0);
        F f025 = static_cast<F>(0.25);
        
        vec3<F> forward = (target - eye).getUnitVector();
        vec3<F> right;

        F dotUp = vec3<F>::dotProduct(up, forward);
        if (std::abs(dotUp) > static_cast<F>(0.9999)) 
        { 
            vec3<F> temporaryUp = std::abs(forward.z) < static_cast<F>(0.999) ? vec3<F>(f0, f0, f1) : vec3<F>(f1, f0, f0); 
            right = vec3<F>::crossProduct(temporaryUp, forward).getUnitVector(); 
        } 
        else 
        { 
            right = vec3<F>::crossProduct(up, forward).getUnitVector(); 
        }
            
        vec3<F> actualUp = vec3<F>::crossProduct(forward, right);  
        
        F m00 = right.x;     F m01 = right.y;     F m02 = right.z;
        F m10 = actualUp.x;  F m11 = actualUp.y;  F m12 = actualUp.z;
        F m20 = forward.x;   F m21 = forward.y;   F m22 = forward.z;
            
        F tr = m00 + m11 + m22;
        F qw, qx, qy, qz;
            

        if (tr > 0.0f) 
        {
            F s = static_cast<F>(std::sqrt(tr + f1) * f2);
            qw = f025 * s;
            qx = (m12 - m21) / s;
            qy = (m20 - m02) / s;
            qz = (m01 - m10) / s;
        } 
        else if ((m00 > m11) && (m00 > m22)) 
        {
            F s = static_cast<F>(std::sqrt(f1 + m00 - m11 - m22) * f2);
            qw = (m12 - m21) / s;
            qx = f025 * s;
            qy = (m01 + m10) / s;
            qz = (m20 + m02) / s;
        } 
        else if (m11 > m22) 
        {
            F s = static_cast<F>(std::sqrt(f1 + m11 - m00 - m22) * f2);
            qw = (m20 - m02) / s;
            qx = (m01 + m10) / s;
            qy = f025 * s;
            qz = (m12 + m21) / s;
        } 
        else 
        {
            F s = static_cast<F>(std::sqrt(f1 + m22 - m00 - m11) * f2);
            qw = (m01 - m10) / s;
            qx = (m20 + m02) / s;
            qy = (m12 + m21) / s;
            qz = f025 * s;
        }
        
        return quat<F>(qw, qx, qy, qz).normalized();
    }


    template<FloatingNumber F>
    inline vec3<F> quat<F>::rotatePoint(const vec3<F>& point, const quat<F>& rot)
    {
        quat<F> q = rot.getUnitQuat();

        vec3<F> u(q.x, q.y, q.z);

        vec3<F> t = u.crossProduct(point) * static_cast<F>(2.0);

        return point + (t * q.w) + u.crossProduct(t);
    }

    template<FloatingNumber F>
    inline vec3<F> quat<F>::rotatePointAroundPivot(const vec3<F>& point, const vec3<F> pivot, const quat<F>& rot)
    {
        vec3<F> vLocal = point - pivot;

        vec3<F> vRotated = quat<F>::rotatePoint(point, rot);

        vec3<F> result = vRotated + pivot;

        return result;
    }

    template<FloatingNumber F>
    inline vec3<F> quat<F>::rotatePoint(const vec3<F>& point) const
    {
        return quat<F>::rotatePoint(point, *this);
    }
    template<FloatingNumber F>
    inline vec3<F> quat<F>::rotatePointAroundPivot(const vec3<F>& point, const vec3<F>& pivot) const
    {
        return quat<F>::rotatePointAroundPivot(point, pivot, *this);
    }


    template<FloatingNumber F> inline quat<F> quat<F>::lerp(const quat<F>& start, const quat<F>& end, F t) 
    { 
        t = math::clamp01(t);
        return quat<F>::lerpUnclamped(start, end, t);
    }

    template<FloatingNumber F> inline quat<F> quat<F>::lerpUnclamped(const quat<F>& start, const quat<F>& end, F t) 
    { 
        F invT = static_cast<F>(1.0) - t; // 1 - t
        return (start * invT + end * t).normalized(); 
    }


    template<FloatingNumber F> inline quat<F> quat<F>::slerp(const quat<F>& start, const quat<F>& end, F t) 
    { 
        t = math::clamp01(t);
        return quat<F>::slerpUnclamped(start, end, t);
    }

    template<FloatingNumber F> inline quat<F> quat<F>::slerpUnclamped(const quat<F>& start, const quat<F>& end, F t) 
    { 
        quat<F> s = start.getUnitQuat();
        quat<F> e = end.getUnitQuat();

        F dot = quat<F>::dotProduct(s, e);

        if (dot < static_cast<F>(0.0))
        {
            e = e * static_cast<F>(-1.0);
            dot = -dot;
        }

        if (dot > static_cast<F>(0.9995))
        {
            return quat<F>::lerpUnclamped(s, e, t);
        }

        F ang = std::acos(dot);
        F sinAng = std::sin(ang);

        F wA = std::sin((static_cast<F>(1.0) - t) * ang) / sinAng;
        F wB = std::sin(t * ang) / sinAng;

        return (s * wA) + (e * wB);
    }

    #pragma endregion

    #pragma region Operators

    template<FloatingNumber F>
    inline quat<F> operator*(const quat<F>& a, const quat<F>& b)
    {
        // Voilà la formule complète : 
        //
        // q' = q1(w1, v1) x q2(w2, v2)
        // q'.w = w1w2 - v1 • v2
        // q'.xyz = w1v2 + w2v1 + v1 x v2
        // 
        // Et la formule développée donne ça : 
        return quat<F>(
            a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
            a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
            a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
            a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w
        );
    }


    template<FloatingNumber F>
    inline quat<F> operator+(const quat<F>& a, const quat<F>& b)
    {
        return quat<F>(
            a.w + b.w,
            a.x + b.x,
            a.y + b.y,
            a.z + b.z
        );
    }

    template<FloatingNumber F>
    inline quat<F> operator-(const quat<F>& a, const quat<F>& b)
    {
        return quat<F>(
            a.w - b.w,
            a.x - b.x,
            a.y - b.y,
            a.z - b.z
        );
    }

    template<FloatingNumber F>
    inline quat<F> operator*(const quat<F>& rot, F scalar)
    {
        return quat<F>(
            rot.w * scalar,
            rot.x * scalar,
            rot.y * scalar,
            rot.z * scalar
        );
    }

    template<FloatingNumber F>
    inline quat<F> operator*(F scalar, const quat<F>& rot)
    {
        return quat<F>(
            rot.w * scalar,
            rot.x * scalar,
            rot.y * scalar,
            rot.z * scalar
        );
    }

    template<FloatingNumber F>
    inline quat<F> operator/(const quat<F>& rot, F scalar)
    {
        if (std::abs(scalar) > math::epsilon<F>())
        {
            F invScalar = static_cast<F>(1.0) / scalar;

            return quat<F>(
                rot.w * invScalar,
                rot.x * invScalar,
                rot.y * invScalar,
                rot.z * invScalar
            );
        }
        else 
        {
            return rot;
        }

    }


    #pragma endregion

}