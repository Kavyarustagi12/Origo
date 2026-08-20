#pragma once

#include "Point_2d.hpp"

class IPath2D
{
public:

    virtual point2d
    PointAtT(
        float t
    ) const = 0;

    virtual float
    Length() const = 0;

    virtual ~IPath2D() = default;
};




class Line2D :
    public IPath2D
{
public:

    Line2D(
        const point2d& a,
        const point2d& b
    );

    point2d
    PointAtT(
        float t
    ) const override;

    float
    Length() const override;

private:

    point2d m_a;
    point2d m_b;

    float m_length;
};




class Arc2D :
    public IPath2D
{
public:

    Arc2D(
        const point2d& start,
        const point2d& center,
        float angleRadians
    );

    point2d
    PointAtT(
        float t
    ) const override;

    float
    Length() const override;

private:

    point2d m_start;
    point2d m_center;

    float m_angle;
    float m_radius;
    float m_length;

    point2d m_startVector;
};