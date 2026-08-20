#pragma once

#include "lattice.hpp"

float BeamSDF(
    const point& p,
    const BeamPrimitive& beam
);

float SphereSDF(
      const point& p,
      const SpherePrimitive& sphere
);