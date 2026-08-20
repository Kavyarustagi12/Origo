#pragma once
#include "point.hpp"
#include <vector>
#include <string>
#include <cstdint>
#include <openvdb/openvdb.h>

class Voxels;

class Mesh
{
public:

    std::vector<openvdb::Vec3s> vertices;

    std::vector<openvdb::Vec3I> triangles;

public:
    Mesh();

    Mesh(
        const Voxels& vox
    );

    void Append(
    const Mesh& other
    );

    uint32_t AddVertex(
    const point& p
    );

    void AddTriangle(
    uint32_t a,
    uint32_t b,
    uint32_t c
    );

    void AddQuad(
    uint32_t a,
    uint32_t b,
    uint32_t c,
    uint32_t d,
    bool flip = false
    );

    std::vector<uint32_t>
    AddVertices(
    const std::vector<point>& pts
    );

    void ExportOBJ(
    const std::string& filename
     ) const;

};

struct Triangle
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
};