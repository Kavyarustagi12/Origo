#pragma once
#include "point.hpp"


class Transform
{
public:

    point translation;

    point rotation;

    point scale;

public:

    Transform();

    point Apply(
        const point&
    ) const;
};