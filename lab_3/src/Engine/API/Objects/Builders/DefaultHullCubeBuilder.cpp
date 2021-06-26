#include "DefaultHullCubeBuilder.hpp"
#include "Engine/Utils/Logger.hpp"
#include "API/Objects/HullModel/HullModelAdapter.hpp"


void DefaultHullCubeBuilder::setWidth(double newWidth)
{
    width = newWidth;
}

std::shared_ptr<ISceneObject> DefaultHullCubeBuilder::build()
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

    auto model = std::make_shared<HullModel>(verts, edges);

    for (int i = 0; i < indices.size(); i += 2)
        model->getEdges().push_back(Edge(model->getVertices()[indices[i]], model->getVertices()[indices[i + 1]]));

    std::shared_ptr<ISceneObject> adaptedModel(new HullModelAdapter(model)); // каша - и модель, и её адаптер создаются тут. Не очень

    adaptedModel->setName(getName());
    adaptedModel->getTransform() = getTransform();

    return adaptedModel;
}
