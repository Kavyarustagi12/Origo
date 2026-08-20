#pragma once

struct point2d
{
    float x;
    float y;

    point2d()
        :
        x(0.0f),
        y(0.0f)
    {
    }

    point2d(
        float x_,
        float y_
    )
        :
        x(x_),
        y(y_)
    {
    }
};