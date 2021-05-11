#include "HullModel.hpp"
#include "Engine/Tools/Logger.hpp"

HullModel::HullModel(VertArray verts, IndArray indices)
    : verts(verts), indices(indices), ISceneObject()
{
}

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
