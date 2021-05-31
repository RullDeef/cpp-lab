#include "DefaultHullCubeBuilder.hpp"
#include "Engine/Utils/Logger.hpp"

DefaultHullCubeBuilder& DefaultHullCubeBuilder::setWidth(double newWidth)
{
    width = newWidth;
    return *this;
}

std::shared_ptr<ISceneObject> DefaultHullCubeBuilder::build(const Transform& t)
{
    double hw = width / 2;
    std::vector<Vertex> verts = {
        { -hw, -hw, -hw },
        {  hw, -hw, -hw },
        { -hw,  hw, -hw },
        {  hw,  hw, -hw },
        { -hw, -hw,  hw },
        {  hw, -hw,  hw },
        { -hw,  hw,  hw },
        {  hw,  hw,  hw }
    };

    std::vector<int> indices = {
        0, 1,    0, 2,    0, 4,    1, 3,
        1, 5,    2, 3,    2, 6,    3, 7,
        4, 5,    4, 6,    5, 7,    6, 7
    };

    std::vector<Edge> edges;

    for (int i = 0; i < indices.size(); i += 2)
        edges.push_back(Edge(verts[indices[i]], verts[indices[i+1]]));

    //std::shared_ptr<ISceneObject> model(new HullModelAdapter(verts, edges));

    //model->setTransform(t);
    return nullptr; // model;
}
