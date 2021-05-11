#include "DefaultHullCubeBuilder.hpp"
#include "Engine/Tools/Logger.hpp"

DefaultHullCubeBuilder& DefaultHullCubeBuilder::setWidth(double newWidth)
{
    width = newWidth;
    return *this;
}

std::shared_ptr<ISceneObject> DefaultHullCubeBuilder::build(const Transform& t)
{
    LOG_FUNC;

    double hw = width / 2;
    HullModel::VertArray verts = {
        { -hw, -hw, -hw },
        {  hw, -hw, -hw },
        { -hw,  hw, -hw },
        {  hw,  hw, -hw },
        { -hw, -hw,  hw },
        {  hw, -hw,  hw },
        { -hw,  hw,  hw },
        {  hw,  hw,  hw }
    };

    HullModel::IndArray indices = {
        0, 1,    0, 2,    0, 4,    1, 3,
        1, 5,    2, 3,    2, 6,    3, 7,
        4, 5,    4, 6,    5, 7,    6, 7
    };

    std::shared_ptr<ISceneObject> model(new HullModel(verts, indices));

    ///TODO: move transform build process in base class
    model->setTransform(t);

    return model;
}
