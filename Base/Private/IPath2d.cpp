#include <../Public/2d_Shape/IPath2d.hpp>



#include <cmath>

Line2D::Line2D(
    const point2d& a,
    const point2d& b
)
    :
    m_a(a),
    m_b(b)
{
    float dx =
        b.x - a.x;

    float dy =
        b.y - a.y;

    m_length =
        std::sqrt(
            dx*dx +
            dy*dy
        );
}

point2d
Line2D::PointAtT(
    float t
) const
{
    return
    {
        m_a.x +
        (m_b.x - m_a.x) * t,

        m_a.y +
        (m_b.y - m_a.y) * t
    };
}

float
Line2D::Length() const
{
    return m_length;
}




Arc2D::Arc2D(
    const point2d& start,
    const point2d& center,
    float angleRadians
)
:
m_start(start),
m_center(center),
m_angle(angleRadians)
{
    m_startVector =
    {
        start.x - center.x,
        start.y - center.y
    };

    m_radius =
        std::sqrt(
            m_startVector.x *
            m_startVector.x +

            m_startVector.y *
            m_startVector.y
        );

    m_length =
        m_radius *
        std::abs(m_angle);
}


point2d
Arc2D::PointAtT(
    float t
) const
{
    float theta =
        m_angle * t;

    float c =
        std::cos(theta);

    float s =
        std::sin(theta);

    point2d rotated;

    rotated.x =
        m_startVector.x * c
        -
        m_startVector.y * s;

    rotated.y =
        m_startVector.x * s
        +
        m_startVector.y * c;

    return
    {
        m_center.x + rotated.x,
        m_center.y + rotated.y
    };
}


float
Arc2D::Length() const
{
    return m_length;
}