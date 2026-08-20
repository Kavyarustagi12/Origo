# Implementation

Origo is structured as a layered geometry pipeline. Geometry begins as a set of **parametric primitives**, is evaluated through **signed-distance functions**, converted into an **OpenVDB level-set representation**, and then composed using volumetric operations.

The implementation currently combines explicit mesh construction with an implicit, field-based geometry pipeline.


<video
  src="https://raw.githubusercontent.com/Kavyarustagi12/Origo/main/assets/2026-04-12-023111.webm"
  controls
  width="100%">
</video>

## Architecture

```text
                         ORIGO
                           │
                           ▼
                Geometry / Parameters
                           │
             ┌─────────────┴─────────────┐
             │                           │
             ▼                           ▼
       Explicit Geometry          Parametric Primitives
          (Mesh)                 (Beams / Spheres)
             │                           │
             │                           ▼
             │                     SDF Evaluation
             │                           │
             │                           ▼
             │                    Spatial Sampling
             │                           │
             │                           ▼
             │                    OpenVDB Level Set
             │                           │
             │              ┌────────────┼────────────┐
             │              ▼            ▼            ▼
             │           Union       Difference   Intersection
             │              │            │            │
             │              └────────────┼────────────┘
             │                           │
             │                           ▼
             │                    Combined Field
             │                           │
             └───────────────────────────┤
                                         ▼
                                Volumetric Geometry
```

## 1. Geometry Representation

The lowest-level geometry operations are built around a lightweight 3D `point` type.

It provides:

* 3D coordinates
* Vector addition and subtraction
* Scalar multiplication and division
* Dot product
* Euclidean length

This type is used throughout the geometry and SDF layers for spatial calculations.

Origo also contains an explicit mesh path. For example, `BaseBox` constructs a cube by defining its eight vertices, applying its dimensions and transformation, and assembling the vertices into six quad faces.

This provides a conventional explicit geometry representation alongside the field-based pipeline.

---

## 2. Parametric Primitives

The procedural side of Origo represents geometry through higher-level primitives rather than directly storing surface topology.

The current lattice representation supports:

* Tapered beams
* Spherical nodes

A beam is defined by:

* Start point
* End point
* Start radius
* End radius
* Cap type

This allows a beam to vary in radius along its length.

A sphere is defined by:

* Center
* Radius

These primitives are stored inside a `Lattice` and become the input to the SDF layer.

The important architectural separation is:

**The lattice describes what should exist; the SDF layer determines its spatial field.**

---

## 3. Signed Distance Functions

Each supported primitive is converted into a signed-distance field.

For a spatial point (p), the SDF describes its position relative to the primitive:

* Negative value → inside
* Zero → surface
* Positive value → outside

### Beam SDF

The beam implementation first determines the beam axis and length, then projects the query point onto that axis.

The axial position is clamped to the beam segment and normalized to obtain a parameter along the beam. The radius is then linearly interpolated between the two endpoint radii.

This produces a distance field for a tapered beam.

Two cap behaviours are currently supported:

* Round
* Flat

### Sphere SDF

The sphere uses the standard signed-distance formulation based on the distance from the query point to the sphere center minus its radius.

This gives Origo a common mathematical interface for evaluating different geometric primitives.

---

## 4. Field Sampling

The SDF exists as a mathematical function, but the volumetric representation requires it to be evaluated at discrete spatial locations.

For each primitive, Origo first calculates a local bounding region around the geometry.

That region is converted into voxel coordinates.

The implementation then iterates through the relevant voxel range:

**World-space position → SDF evaluation → distance value → voxel**

This keeps sampling localized to the region occupied by the primitive instead of evaluating the entire volume.

The current lattice rendering path uses a voxel spacing of `0.05` for this sampling process.

---

## 5. OpenVDB Representation

The sampled distance values are stored in an OpenVDB `FloatGrid`.

The grid is configured as a:

**Level Set**

This gives Origo a sparse volumetric representation of the geometry instead of immediately converting everything into polygonal surfaces.

The resulting representation can therefore be treated as a spatial scalar field rather than simply a list of vertices and faces.

Conceptually:

**Primitive → SDF → Sampled Scalar Field → OpenVDB Level Set**

---

## 6. Volumetric Composition

Once geometry is represented as a distance field, multiple objects can be composed directly in the volumetric domain.

Origo currently provides:

* **Union**
* **Difference**
* **Intersection**

These operations are implemented through OpenVDB's CSG functionality.

This means complex geometry can be constructed by combining fields rather than manually modifying mesh topology.

For example:

**Beam field + Sphere field → Combined volumetric geometry**

or:

**Base geometry − Subtractive field → Modified geometry**

---

## 7. Gyroid Integration

Origo also supports combining geometry with a mathematically defined gyroid field.

The gyroid provides its own signed-distance evaluation.

During intersection, Origo evaluates the gyroid field at the active OpenVDB voxel locations and combines the gyroid distance with the existing object distance.

The result is another implicit field representing the intersection between the object and the gyroid structure.

This provides a mechanism for introducing mathematically defined internal structures without explicitly modelling every resulting surface.

---

## 8. Overall Data Flow

The current implementation can therefore be summarized as:

**Geometry Parameters**

↓

**Primitive Construction**

Beams / Spheres / Explicit Mesh Objects

↓

**Mathematical Representation**

Signed Distance Functions

↓

**Spatial Evaluation**

Local bounding region + voxel sampling

↓

**Volumetric Representation**

OpenVDB `FloatGrid` Level Set

↓

**Field Composition**

Union / Difference / Intersection / Gyroid operations

↓

**Resulting Volumetric Geometry**

---

## Design Principle

The central architectural idea is the separation between **geometry description** and **geometry representation**.

A primitive does not need to begin as a collection of final surfaces.

It can first exist as:

**Parameters → Mathematical Function → Spatial Field**

and only later be converted into the representation required by the application.

This is the direction Origo is exploring: moving part of the geometry-generation process from explicit surface construction toward **procedural and implicit mathematical representations**.
