
#include "../Public/sdf_math.hpp"

#include <cmath>

static float Clamp(
    float v,
    float min,
    float max)
{
    if (v < min)
        return min;

    if (v > max)
        return max;

    return v;
}

float BeamSDF(
    const point& p,
    const BeamPrimitive& beam)
{
    // =========================================
    // BEAM AXIS
    // =========================================

    point ba =
        beam.b - beam.a;

    // =========================================
    // BEAM LENGTH
    // =========================================

    float length =
        ba.Length();

    // =========================================
    // SAFETY
    // =========================================

    if (length < 0.0001f)
    {
        return 1000.0f;
    }

    // =========================================
    // NORMALIZED DIRECTION
    // =========================================

    point dir =
        ba / length;

    // =========================================
    // POINT RELATIVE TO START
    // =========================================

    point pa =
        p - beam.a;

    // =========================================
    // AXIAL POSITION
    // =========================================

    float h =
        pa.Dot(dir);

    // =========================================
    // ROUND CAPSULE BEAM
    // =========================================

    if (beam.cap == BeamCap::Round)
    {
        // =====================================
        // CLAMP TO SEGMENT
        // =====================================

        float hc =
            Clamp(
                h,
                0.0f,
                length
            );

        // =====================================
        // NORMALIZED POSITION
        // =====================================

        float t =
            hc / length;

        // =====================================
        // INTERPOLATED RADIUS
        // =====================================

        float radius =
            beam.radiusA * (1.0f - t)
            + beam.radiusB * t;

        // =====================================
        // CLOSEST POINT
        // =====================================

        point closest =
            beam.a + dir * hc;

        // =====================================
        // CAPSULE DISTANCE
        // =====================================

        return
            (p - closest).Length()
            - radius;
    }

    // =========================================
    // FLAT TAPERED BEAM
    // =========================================
else
{
    // =====================================
    // OUTSIDE START CAP
    // =====================================

    if (h < 0.0f)
    {
        float radius =
            beam.radiusA;

        point capPoint =
            beam.a;

        point radialVec =
            p - capPoint;

        // remove axial component
        radialVec =
            radialVec
            - dir * radialVec.Dot(dir);

        float radial =
            radialVec.Length()
            - radius;

        return std::sqrt(
            radial * radial
            + h * h
        );
    }

    // =====================================
    // OUTSIDE END CAP
    // =====================================

    if (h > length)
    {
        float radius =
            beam.radiusB;

        point capPoint =
            beam.b;

        point radialVec =
            p - capPoint;

        radialVec =
            radialVec
            - dir * radialVec.Dot(dir);

        float radial =
            radialVec.Length()
            - radius;

        float axial =
            h - length;

        return std::sqrt(
            radial * radial
            + axial * axial
        );
    }

    // =====================================
    // INSIDE AXIAL RANGE
    // =====================================

    float t =
        h / length;

    float radius =
        beam.radiusA * (1.0f - t)
        + beam.radiusB * t;

    point axisPoint =
        beam.a + dir * h;

    return
        (p - axisPoint).Length()
        - radius;
}
}

float SphereSDF(
      const point& p,
      const SpherePrimitive& sphere
){
    point rvector= p- sphere.center;
    return rvector.Length() - sphere.radius;
}