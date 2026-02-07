#pragma once 

#include <cmath>

#include "Math\Angle.hpp"
#include "Math\Vector2.hpp"
#include "Math\Vector3.hpp"
#include "Math\Quaternion.hpp"
#include "Math\Matrix4x4.hpp"

namespace Mathematics
{
    // ----------- Angle.hpp --------------
    inline angle angle::angleBetween(const vec2& a, const vec2& b)
    {
        //
        // Soit v et u des vecteurs
        //
        // v • u = ||v|| ||u|| cos(θ)
        //
        //            (   v • u   )
        //  θ = arccos(-----------)
        //            (||v|| ||u||)
        //
        //          ↑↑↑↑↑↑↑↑↑
        //       comes from here

        float dot = vec2::dotProduct(a.getUnitVector(), b.getUnitVector());

        return angle::fromRadians(std::acos(MathInternal::clamp(dot, -1.0f, 1.0f)));
    }

    // ----------- Vector2.hpp --------------

    inline vec2 vec2::fromAngle(const angle& angle)
    { 
        return vec2(std::cos(angle.asRadians()), std::sin(angle.asRadians())); 
    }

    // ----------- Vector3.hpp --------------

    inline vec3::vec3(const vec2& xy) : m_X(xy.x()), m_Y(xy.y()), m_Z(0.0f) {}
    inline vec3::vec3(const vec2& xy, float vz) : m_X(xy.x()), m_Y(xy.y()), m_Z(vz) {}

    vec3::operator vec2() const { return vec2(m_X, m_Y); }

    inline vec2 vec3::xx() const { return vec2(m_X, m_X); }
    inline vec2 vec3::yy() const { return vec2(m_Y, m_Y); }
    inline vec2 vec3::zz() const { return vec2(m_Z, m_Z); }
    inline vec2 vec3::xy() const { return vec2(m_X, m_Y); }
    inline vec2 vec3::xz() const { return vec2(m_X, m_Z); }
    inline vec2 vec3::yx() const { return vec2(m_Y, m_X); }
    inline vec2 vec3::yz() const { return vec2(m_Y, m_Z); }
    inline vec2 vec3::zx() const { return vec2(m_Z, m_X); }
    inline vec2 vec3::zy() const { return vec2(m_Z, m_Y); }

    // ----------- Quaternion.hpp --------------

    inline quat::quat(float qw, const vec3& xyz) : m_W(qw), m_X(xyz.x()), m_Y(xyz.y()), m_Z(xyz.z()) {}

    inline vec3 quat::xyz() const { return vec3(m_X, m_Y, m_Z); }
    inline vec3 quat::zyx() const { return vec3(m_Z, m_Y, m_X); }

    inline quat quat::fromAxisAngle(vec3 axis, float angle)
    {
        axis = axis.normalized();
        float theta = (angle * Constants::DegToRad) / 2.0f;

        float w = std::cos(theta);
        float x = axis.x() * std::sin(theta);
        float y = axis.y() * std::sin(theta);
        float z = axis.z() * std::sin(theta);

        return quat(w, x, y, z);
    }

    inline quat quat::fromEuler(const vec3& rotation)
    {
        // the Hamilton product is still not implemented

        float phi = (rotation.x() * Constants::DegToRad) / 2.0f;
        float theta = (rotation.y() * Constants::DegToRad) / 2.0f;
        float psi = (rotation.z() * Constants::DegToRad) / 2.0f;

        float cosPhi = std::cosf(phi);
        float cosTheta = std::cosf(theta);
        float cosPsi = std::cosf(psi);
        float sinPhi = std::sinf(phi);
        float sinTheta = std::sinf(theta);
        float sinPsi = std::sinf(psi);

        float w = cosPhi * cosTheta * cosPsi + sinPhi * sinTheta * sinPsi;
        float x = sinPhi * cosTheta * cosPsi - cosPhi * sinTheta * sinPsi;
        float y = cosPhi * sinTheta * cosPsi + sinPhi * cosTheta * sinPsi;
        float z = cosPhi * cosTheta * sinPsi - sinPhi * sinTheta * cosPsi;

        return quat(w, x, y, z);
    }

    inline vec3 quat::rotatePointViaQuat(const vec3 &point, const quat &rot)
    {
        quat qPoint = quat(0.0f, point.xyz());
        
        vec3 rotated = (rot * qPoint * rot.getConjugatedQuat()).xyz();

        return rotated;
    }

    inline vec3 quat::toEuler() const
    {
        float x = std::asinf(2 * (m_W * m_X - m_X * m_Z));
        float y = std::atan2f(2 * (m_W * m_X + m_Y * m_X), 1 - 2 * (m_X * m_X + m_Y * m_Y));
        float z = std::atan2f(2 * (m_W * m_Z + m_X * m_Y), 1 - 2 * (m_X * m_X + m_Z * m_Z));

        return vec3(x, y, z);
    }

    inline quat operator*(const quat &a, const quat &b)
    {
        quat qa = a.getUnitQuat();
        quat qb = b.getUnitQuat();

        float w = qa.w() * qb.w() - vec2::dotProduct(qa.xyz(), qb.xyz()); 

        vec3 xyz = qb.xyz() * qa.w() + qa.xyz() * qb.w() + vec3::crossProduct(qa.xyz(), qb.xyz());

        return quat(w, xyz);
    }

    inline mat4 quat::toMat4() const 
    {
        float xx = m_X * m_X;
        float yy = m_Y * m_Y;
        float zz = m_Z * m_Z;
        float xy = m_X * m_Y;
        float wz = m_W * m_Z;
        float wy = m_W * m_Y;
        float wx = m_W * m_X;
        float xz = m_X * m_Z;
        float yz = m_Y * m_Z;

        return mat4(1 - 2 * (yy + zz), 2 * (xy - wz), 2 * (xz + wy), 0.0f,
                    2 * (xy + wz), 1 - 2 * (xx + zz), 2 * (yz - wx), 0.0f,
                    2 * (xz - wy), 2 * (yz + wx), 1 - 2 * (xx + yy), 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
    }
}