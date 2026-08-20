#pragma once


class point
{
public:

float x,y,z;

point();

point(float x,float y,float z);

point operator+(
    const point& b
) const;

point operator-(
    const point& b
) const;

point operator*(
    float s
) const;

point operator/(
    float s
) const;

float Dot(
    const point& b
) const;

float Length() const;

};