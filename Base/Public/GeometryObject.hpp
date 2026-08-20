#pragma once

#include "transformation.hpp"
#include "mesh.hpp"

class GeometryObject
{
public:

    Transform transform;

public:

    virtual Mesh Build() const = 0;

    virtual ~GeometryObject() = default;
};



class BaseBox :
    public GeometryObject
{
public:

    point size;

public:
    BaseBox();
    BaseBox(const point& size);

    Mesh Build() const override;
};