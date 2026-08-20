#include "../Public/transformation.hpp"


Transform::Transform()
{
    translation =
    {
        0,
        0,
        0
    };

    rotation =
    {
        0,
        0,
        0
    };

    scale =
    {
        1,
        1,
        1
    };
}

point Transform::Apply(
    const point& p
) const
{
    point result = p;

    result.x *= scale.x;
    result.y *= scale.y;
    result.z *= scale.z;

    result.x += translation.x;
    result.y += translation.y;
    result.z += translation.z;

    return result;
}