#pragma once

#include <vector>
#include "../ISceneObject.hpp"

class HullModel : public ISceneObject
{
public:
    using VertArray = std::vector<Vector>;
    using IndArray = std::vector<unsigned int>;

    HullModel() = default;
    HullModel(VertArray verts, IndArray indices);

    virtual void draw(std::shared_ptr<IRenderer> renderer) const override;

private:
    VertArray verts;
    IndArray indices;
};
