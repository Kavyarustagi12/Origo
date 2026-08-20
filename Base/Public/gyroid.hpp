#pragma once

#include "point.hpp"

class Gyroid
{
public:

    Gyroid(
        float unitSize,
        float thickness
    );

    float SignedDistance(
        const point& p
    ) const;

private:

    float m_unitSize;
    float m_thickness;
};