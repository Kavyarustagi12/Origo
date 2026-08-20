

#include <fstream>
#include "../Public/mesh.hpp"

#include "../Public/voxels.hpp"

#include <openvdb/tools/VolumeToMesh.h>

Mesh::Mesh(
    const Voxels& vox)
{


    openvdb::tools::VolumeToMesh mesher(
        0.0,   // isovalue
        0.0    // adaptivity
    );


    mesher(
        *vox.grid
    );



    for (size_t i = 0;
         i < mesher.pointListSize();
         i++)
    {
        vertices.push_back(
            mesher.pointList()[i]
        );
    }



    for (size_t n = 0;
         n < mesher.polygonPoolListSize();
         n++)
    {
        const auto& pool =
            mesher.polygonPoolList()[n];



        for (size_t i = 0;
             i < pool.numTriangles();
             i++)
        {
            auto tri =
                pool.triangle(i);

            triangles.push_back(
                openvdb::Vec3I(
                    tri[0],
                    tri[1],
                    tri[2]
                )
            );
        }


        for (size_t i = 0;
             i < pool.numQuads();
             i++)
        {
            auto quad =
                pool.quad(i);



            triangles.push_back(
                openvdb::Vec3I(
                    quad[0],
                    quad[1],
                    quad[2]
                )
            );

            triangles.push_back(
                openvdb::Vec3I(
                    quad[0],
                    quad[2],
                    quad[3]
                )
            );
        }
    }
}
Mesh::Mesh(){

}


void Mesh::Append(
    const Mesh& other
)
{
    const int offset =
        static_cast<int>(
            vertices.size()
        );

    // copy vertices

    vertices.insert(
        vertices.end(),
        other.vertices.begin(),
        other.vertices.end()
    );

    // copy triangles with offset

    for(const auto& tri :
        other.triangles)
    {
        triangles.emplace_back(
            tri.x() + offset,
            tri.y() + offset,
            tri.z() + offset
        );
    }
}


std::vector<uint32_t>
Mesh::AddVertices(
    const std::vector<point>& pts
)
{
    std::vector<uint32_t> ids;

    for(const auto& p : pts)
    {
        ids.push_back(
            AddVertex(p)
        );
    }

    return ids;
}


uint32_t Mesh::AddVertex(
    const point& p
)
{
    vertices.emplace_back(
        p.x,
        p.y,
        p.z
    );

    return
        static_cast<uint32_t>(
            vertices.size()-1
        );
}

void Mesh::AddTriangle(
    uint32_t a,
    uint32_t b,
    uint32_t c
)
{
    triangles.emplace_back(
        a,
        b,
        c
    );
}

void Mesh::AddQuad(
    uint32_t a,
    uint32_t b,
    uint32_t c,
    uint32_t d,
    bool flip
)
{
    if(!flip)
    {
        AddTriangle(a,b,c);
        AddTriangle(a,c,d);
    }
    else
    {
        AddTriangle(d,c,b);
        AddTriangle(d,b,a);
    }
}

void Mesh::ExportOBJ(
    const std::string& filename) const
{
    std::ofstream file(
        filename
    );


    for (const auto& v : vertices)
    {
        file
            << "v "
            << v.x() << " "
            << v.y() << " "
            << v.z() << "\n";
    }


    for (const auto& t : triangles)
    {
        file
            << "f "
            << t.x() + 1 << " "
            << t.y() + 1 << " "
            << t.z() + 1 << "\n";
    }

    file.close();
}