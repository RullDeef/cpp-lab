#include "HullModel.hpp"
#include "Engine/Utils/Logger.hpp"

HullModel::HullModel(std::vector<Vertex> verts, std::vector<Edge> edges)
    : vertices(verts), edges(edges)
{
}

/*
void HullModel::draw(std::shared_ptr<IRenderer> renderer) const
{
    renderer->saveMatrix();
    renderer->multiplyMatrix(getTransform());

    for (size_t i = 0; i < indices.size(); i += 2)
    {
        const Vector& p1 = verts[indices[i]];
        const Vector& p2 = verts[indices[i + 1]];

        renderer->drawLine(p1, p2);
    }

    renderer->restoreMatrix();
}
*/
