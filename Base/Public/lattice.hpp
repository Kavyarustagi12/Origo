#pragma once

#include <vector>

#include "point.hpp"

enum class BeamCap
{
    Round,
    Flat
};

struct BeamPrimitive
{
    point a;
    point b;

    float radiusA;
    float radiusB;

    BeamCap cap = BeamCap::Round;
};

struct SpherePrimitive
{
    point center;
    float radius;
};

class Lattice
{
public:

    std::vector<BeamPrimitive> beams;
    std::vector<SpherePrimitive> spheres;

public:

    void AddBeam(
        const point& a,
        float radiusA,
        const point& b,
        float radiusB,
        bool roundCap = true
    );

    void AddBeam(
        const point& a,
        const point& b,
        float radiusA,
        float radiusB,
        bool roundCap = true
    );

    void AddSphere(
        const point& center,
        float radius
    );
};