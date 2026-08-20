# pragma once
#include "point.hpp"
#include "mesh.hpp"
#include <vector>
#include <cmath>

point Lerp(
    const point& a,
    const point& b,
    float t
);


class PointGrid
{
public:

    int width;
    int height;

    std::vector<point> points;

public:

    PointGrid(
        int w,
        int h
    );

    point& At(
        int x,
        int y
    );

    const point& At(
        int x,
        int y
    ) const;
};


PointGrid SubdivideQuad(
    int subX,
    int subY,

    const point& A,
    const point& B,
    const point& C,
    const point& D
);

std::vector<uint32_t>
StoreGridVertices(
    Mesh& mesh,
    const PointGrid& grid
);

void AddGridQuads(
    Mesh& mesh,

    const PointGrid& grid,

    const std::vector<uint32_t>& ids
);



float Gaussian2D(
    float x,
    float y,
    float sigmaX = 0.2f,
    float sigmaY = 0.2f
);



void ModulateGridGaussian(
    PointGrid& grid,
    const point& normal,
    float height = 20.0f
);

