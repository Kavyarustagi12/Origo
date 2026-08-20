#include "../Public/voxels.hpp"
#include <algorithm>

#include <openvdb/openvdb.h>
#include <openvdb/math/Transform.h>
#include <openvdb/tools/Composite.h>
#include "../Public/gyroid.hpp"

Voxels::Voxels()
{


    grid =
        openvdb::FloatGrid::create(
            1000.0f
        );


    grid->setTransform(
        openvdb::math::Transform::createLinearTransform(
            1.0
        )
    );


    grid->setGridClass(
        openvdb::GRID_LEVEL_SET
    );

    grid->setName(
        "LexicaVoxels"
    );
}

Voxels::Voxels(
    const Lattice& lattice)
    : Voxels()
{
    RenderLattice(lattice);
}

void Voxels::RenderLattice(
    const Lattice& lattice)
{

    auto accessor =
        grid->getAccessor();


    constexpr float voxelSize = 0.05;

if(!lattice.beams.empty())
  {  
    for (const auto& beam : lattice.beams)
    {

        float maxRadius =
            std::max(
                beam.radiusA,
                beam.radiusB
            );

        float padding =
            maxRadius + 2.0f;

        float minX =
            std::min(
                beam.a.x,
                beam.b.x
            ) - padding;

        float minY =
            std::min(
                beam.a.y,
                beam.b.y
            ) - padding;

        float minZ =
            std::min(
                beam.a.z,
                beam.b.z
            ) - padding;

        float maxX =
            std::max(
                beam.a.x,
                beam.b.x
            ) + padding;

        float maxY =
            std::max(
                beam.a.y,
                beam.b.y
            ) + padding;

        float maxZ =
            std::max(
                beam.a.z,
                beam.b.z
            ) + padding;


        int ix0 =
            static_cast<int>(
                floor(minX / voxelSize)
            );

        int iy0 =
            static_cast<int>(
                floor(minY / voxelSize)
            );

        int iz0 =
            static_cast<int>(
                floor(minZ / voxelSize)
            );

        int ix1 =
            static_cast<int>(
                ceil(maxX / voxelSize)
            );

        int iy1 =
            static_cast<int>(
                ceil(maxY / voxelSize)
            );

        int iz1 =
            static_cast<int>(
                ceil(maxZ / voxelSize)
            );

        for (int z = iz0; z <= iz1; z++)
        {
            for (int y = iy0; y <= iy1; y++)
            {
                for (int x = ix0; x <= ix1; x++)
                {


                    point p(
                        x * voxelSize,
                        y * voxelSize,
                        z * voxelSize
                    );


                    float d =
                        BeamSDF(
                            p,
                            beam
                        );


                    openvdb::Coord ijk(
                        x,
                        y,
                        z
                    );


                    float current =
                        accessor.getValue(
                            ijk
                        );


                    if (d < current)
                    {
                        accessor.setValue(
                            ijk,
                            d
                        );
                    }
                }
            }
        }
    }
}
if(!lattice.spheres.empty()){
      for(const auto & sphere :lattice.spheres){
        float padding = sphere.radius + 2.0f;
        float minX=sphere.center.x - padding;
        float minY=sphere.center.y - padding;
        float minZ=sphere.center.z - padding;
        float maxX=sphere.center.x + padding;
        float maxY=sphere.center.y + padding;
        float maxZ=sphere.center.z + padding;
                int ix0 =
            static_cast<int>(
                floor(minX / voxelSize)
            );

        int iy0 =
            static_cast<int>(
                floor(minY / voxelSize)
            );

        int iz0 =
            static_cast<int>(
                floor(minZ / voxelSize)
            );

        int ix1 =
            static_cast<int>(
                ceil(maxX / voxelSize)
            );

        int iy1 =
            static_cast<int>(
                ceil(maxY / voxelSize)
            );

        int iz1 =
            static_cast<int>(
                ceil(maxZ / voxelSize)
            );

        for (int z = iz0; z <= iz1; z++)
        {
            for (int y = iy0; y <= iy1; y++)
            {
                for (int x = ix0; x <= ix1; x++)
                {


                    point p(
                        x * voxelSize,
                        y * voxelSize,
                        z * voxelSize
                    );


                    float d =
                        SphereSDF(
                            p,
                            sphere
                        );


                    openvdb::Coord ijk(
                        x,
                        y,
                        z
                    );


                    float current =
                        accessor.getValue(
                            ijk
                        );


                    if (d < current)
                    {
                        accessor.setValue(
                            ijk,
                            d
                        );
                    }
                }
            }
        }

      }
}
}

void Voxels::BoolUnion(
    const Voxels& other)
{
    openvdb::tools::csgUnion(
        *grid,
        *other.grid
    );
}

void Voxels::BoolSubtract(
    const Voxels& other)
{
    openvdb::tools::csgDifference(
        *grid,
        *other.grid
    );
}

void Voxels::BoolIntersect(
    const Voxels& other)
{
    openvdb::tools::csgIntersection(
        *grid,
        *other.grid
    );
}

void Voxels::IntersectGyroid(
    const Gyroid& gyroid)
{
    auto accessor =
        grid->getAccessor();

    constexpr float voxelSize = 0.5f;

    for (auto iter =
            grid->beginValueOn();

         iter.test();

         ++iter)
    {
        openvdb::Coord coord =
            iter.getCoord();

        point p(
            coord.x() * voxelSize,
            coord.y() * voxelSize,
            coord.z() * voxelSize
        );

        // =================================
        // CURRENT OBJECT DISTANCE
        // =================================

        float objectDist =
            *iter;

        // =================================
        // GYROID DISTANCE
        // =================================

        float gyroidDist =
            gyroid.SignedDistance(
                p
            );

        // =================================
        // INTERSECTION
        // =================================

        float result =
            std::max(
                objectDist,
                gyroidDist
            );

        accessor.setValue(
            coord,
            result
        );
    }
}