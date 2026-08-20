#include "../Public/utility.hpp"

point Lerp(
    const point& a,
    const point& b,
    float t
)
{
    return
    {
        a.x + (b.x - a.x) * t,
        a.y + (b.y - a.y) * t,
        a.z + (b.z - a.z) * t
    };
}

PointGrid::PointGrid(
    int w,
    int h
)
:
width(w),
height(h),
points(w*h)
{
}


point& PointGrid::At(
    int x,
    int y
)
{
    return
        points[
            y * width + x
        ];
}

const point& PointGrid::At(
    int x,
    int y
) const
{
    return
        points[
            y * width + x
        ];
}

PointGrid SubdivideQuad(
    int subX,
    int subY,

    const point& A,
    const point& B,
    const point& C,
    const point& D
)
{
    PointGrid grid(
        subX,
        subY
    );

    for(int x=0; x<subX; x++)
    {
        for(int y=0; y<subY; y++)
        {
            float tx =
                float(x) /
                float(subX - 1);

            float ty =
                float(y) /
                float(subY - 1);

            point top =
                Lerp(
                    A,
                    B,
                    tx
                );

            point bottom =
                Lerp(
                    D,
                    C,
                    tx
                );

            grid.At(x,y) =
                Lerp(
                    top,
                    bottom,
                    ty
                );
        }
    }

    return grid;
}


std::vector<uint32_t>
StoreGridVertices(
    Mesh& mesh,
    const PointGrid& grid
)
{
    std::vector<uint32_t> ids(
        grid.width *
        grid.height
    );

    for(int x=0;
        x<grid.width;
        x++)
    {
        for(int y=0;
            y<grid.height;
            y++)
        {
            ids[
                y * grid.width + x
            ]
            =
            mesh.AddVertex(
                grid.At(x,y)
            );
        }
    }

    return ids;
}


void AddGridQuads(
    Mesh& mesh,

    const PointGrid& grid,

    const std::vector<uint32_t>& ids
)
{
    for(int x=0;
        x<grid.width-1;
        x++)
    {
        for(int y=0;
            y<grid.height-1;
            y++)
        {
            uint32_t n0 =
                ids[
                    y*grid.width+x
                ];

            uint32_t n1 =
                ids[
                    (y+1)*grid.width+x
                ];

            uint32_t n2 =
                ids[
                    (y+1)*grid.width+(x+1)
                ];

            uint32_t n3 =
                ids[
                    y*grid.width+(x+1)
                ];

            mesh.AddQuad(
                n0,
                n3,
                n2,
                n1
            );
        }
    }
}





float Gaussian2D(
    float x,
    float y,
    float sigmaX,
    float sigmaY
)
{
    float expX =
        std::pow(
            x - 0.5f,
            2.0f
        )
        /
        (
            2.0f *
            std::pow(
                sigmaX,
                2.0f
            )
        );

    float expY =
        std::pow(
            y - 0.5f,
            2.0f
        )
        /
        (
            2.0f *
            std::pow(
                sigmaY,
                2.0f
            )
        );

    return
        std::exp(
            -(expX + expY)
        );
}



void ModulateGridGaussian(
    PointGrid& grid,
    const point& normal,
    float height
)
{
    int width  = grid.width;
    int heightCount = grid.height;

    // Skip edges intentionally
    for(int x = 1;
        x < width - 1;
        x++)
    {
        for(int y = 1;
            y < heightCount - 1;
            y++)
        {
            float tx =
                float(x)
                /
                float(width - 1);

            float ty =
                float(y)
                /
                float(heightCount - 1);

            float g =
                Gaussian2D(
                    tx,
                    ty
                );

            grid.At(x,y).x +=
                normal.x *
                g *
                height;

            grid.At(x,y).y +=
                normal.y *
                g *
                height;

            grid.At(x,y).z +=
                normal.z *
                g *
                height;
        }
    }
}




