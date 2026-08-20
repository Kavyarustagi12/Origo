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



    Lattice lattice;


    const int steps =
        45;

    const float heightStep =
        1.5f;

    const float helixRadius =
        5.0f;

    const float beamRadius =
        0.7f;

    point prevA;
    point prevB;

    bool first =
        true;

   
    for (int i = 0; i < steps; i++)
    {
        float t =
            i * 0.35f;

        float z =
            i * heightStep;

       

        point a(
            std::cos(t) * helixRadius,
            std::sin(t) * helixRadius,
            z
        );

      
        point b(
            std::cos(t + PI) * helixRadius,
            std::sin(t + PI) * helixRadius,
            z
        );

        if (!first)
        {
        

            lattice.AddBeam(
                prevA,
                beamRadius,

                a,
                beamRadius,

                true
            );

            lattice.AddBeam(
                prevB,
                beamRadius,

                b,
                beamRadius,

                true
            );

          

            lattice.AddBeam(
                a,
                beamRadius * 0.75f,

                b,
                beamRadius * 0.75f,

                true
            );
        }

        prevA = a;
        prevB = b;

        first = false;
    }

   

    Voxels vox(
        lattice
    );

    
    Mesh mesh(
        vox
    );


    mesh.ExportOBJ(
        "storage_friendly_helix.obj"
    );


    return 0;
}