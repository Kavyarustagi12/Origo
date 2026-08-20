#include "../Public/point.hpp"
#include <cmath>


point::point()
{
    x=0.0f;
    y=0.0f;
    z=0.0f;

}

point::point(float x, float y,float z):x(x),y(y),z(z){}


point point::operator+(
    const point& b) const
{
    return point(
        x + b.x,
        y + b.y,
        z + b.z
    );
}

point point::operator-(
    const point& b) const
{
    return point(
        x - b.x,
        y - b.y,
        z - b.z
    );
}

point point::operator*(
    float s) const
{
    return point(
        x * s,
        y * s,
        z * s
    );
}

point point::operator/(
    float s) const
{
    return point(
        x / s,
        y / s,
        z / s
    );
}

float point::Dot(
    const point& b) const
{
    return
        x * b.x +
        y * b.y +
        z * b.z;
}

float point::Length() const{
    return std::sqrt(x*x +
    y*y + z*z );
}


