#include "../Public/lattice.hpp"

void Lattice::AddBeam(
    const point& a,
    float radiusA,
    const point& b,
    float radiusB,
    bool roundCap)
{
    BeamPrimitive beam;

    beam.a = a;
    beam.b = b;

    beam.radiusA = radiusA;
    beam.radiusB = radiusB;

    beam.cap =
        roundCap
        ? BeamCap::Round
        : BeamCap::Flat;

    beams.push_back(beam);
}

void Lattice::AddBeam(
    const point& a,
    const point& b,
    float radiusA,
    float radiusB,
    bool roundCap)
{
    AddBeam(
        a,
        radiusA,
        b,
        radiusB,
        roundCap
    );
}

void Lattice::AddSphere(
    const point& center,
    float radius
)
{
    SpherePrimitive sphere;
    sphere.center=center;
    sphere.radius=radius;
    spheres.push_back(sphere);

}