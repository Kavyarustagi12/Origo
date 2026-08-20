#pragma once

#include <openvdb/openvdb.h>

#include "sdf_math.hpp"

#include <openvdb/tools/Composite.h>

#include "gyroid.hpp"

class Lattice;

class Voxels
{
public:

    openvdb::FloatGrid::Ptr grid;

public:

    Voxels();

    Voxels(
        const Lattice& lattice
    );

    void BoolUnion(
    const Voxels& other
    );

    void BoolSubtract(
    const Voxels& other
    );

    void BoolIntersect(
    const Voxels& other
    );

    void IntersectGyroid(
    const Gyroid& gyroid
    );

private:

    void RenderLattice(
        const Lattice& lattice
    );
};