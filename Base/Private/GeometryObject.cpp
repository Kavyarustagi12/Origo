#include "../Public/GeometryObject.hpp"

BaseBox::BaseBox()
{
    size =
    {
        1,
        1,
        1
    };
}
BaseBox::BaseBox(const point& size):size(size){};



Mesh BaseBox::Build()const {

Mesh mesh;
std::vector<point> verts =
{
    {-0.5f,-0.5f,-0.5f},
    { 0.5f,-0.5f,-0.5f},
    { 0.5f, 0.5f,-0.5f},
    {-0.5f, 0.5f,-0.5f},

    {-0.5f,-0.5f, 0.5f},
    { 0.5f,-0.5f, 0.5f},
    { 0.5f, 0.5f, 0.5f},
    {-0.5f, 0.5f, 0.5f}
};

for(auto& v : verts)
{
    v.x *= size.x;
    v.y *= size.y;
    v.z *= size.z;

  v=transform.Apply(v);
}

auto ids =
    mesh.AddVertices(
        verts
    );

mesh.AddQuad(
    ids[3],
    ids[2],
    ids[1],
    ids[0]
);

mesh.AddQuad(
    ids[4],
    ids[5],
    ids[6],
    ids[7]
);

mesh.AddQuad(
    ids[1],
    ids[5],
    ids[4],
    ids[0]
);

mesh.AddQuad(
    ids[7],
    ids[6],
    ids[2],
    ids[3]
);

mesh.AddQuad(
    ids[4],
    ids[7],
    ids[3],
    ids[0]
);

mesh.AddQuad(
    ids[2],
    ids[6],
    ids[5],
    ids[1]
);

return mesh;
}