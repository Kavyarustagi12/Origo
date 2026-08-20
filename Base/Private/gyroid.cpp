#include "../Public/gyroid.hpp"

#include <cmath>

Gyroid::Gyroid(
    float unitSize,
    float thickness)
{
    m_unitSize =
        unitSize;

    m_thickness =
        thickness;
}

float Gyroid::SignedDistance(
    const point& p) const
{
    // =====================================
    // SCALE SPACE
    // =====================================

    float x =
        p.x / m_unitSize;

    float y =
        p.y / m_unitSize;

    float z =
        p.z / m_unitSize;

    // =====================================
    // GYROID EQUATION
    // =====================================

    float g =
        std::sin(x) * std::cos(y)
        +
        std::sin(y) * std::cos(z)
        +
        std::sin(z) * std::cos(x);

    // =====================================
    // THICKEN SURFACE
    // =====================================

    return
        std::abs(g)
        - m_thickness;
}