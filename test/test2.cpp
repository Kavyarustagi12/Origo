#include <iostream>
#include <cmath>

#include <openvdb/openvdb.h>

#include "lattice.hpp"
#include "voxels.hpp"
#include "mesh.hpp"

constexpr float PI =
    3.14159265359f;

int main()
{
    

    openvdb::initialize();
    
Mesh mesh;

std::vector<point> pts =
{
    {0,0,0},     // 0
    {10,0,0},    // 1
    {10,10,0},   // 2
    {0,10,0},    // 3

    {0,0,15},    // 4
    {10,0,15},   // 5
    {10,10,15},  // 6
    {0,10,15}    // 7
};

auto ids =
    mesh.AddVertices(pts);
mesh.AddQuad(
    ids[3],
    ids[2],
    ids[1],
    ids[0]
);
mesh.AddQuad(
    ids[4],
    ids[5],
    ids[6],
    ids[7]
);
mesh.AddQuad(
    ids[1],
    ids[5],
    ids[4],
    ids[0]
);
mesh.AddQuad(
    ids[7],
    ids[6],
    ids[2],
    ids[3]
);
mesh.AddQuad(
    ids[4],
    ids[7],
    ids[3],
    ids[0]
);
mesh.AddQuad(
    ids[2],
    ids[6],
    ids[5],
    ids[1]
);

mesh.ExportOBJ(
    "cube.obj"
);

    return 0;
}