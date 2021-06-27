#include "WireframeModelBuilder.hpp"
#include "Utils/Logger.hpp"


void WireframeModelBuilder::addVertex(const Vertex& vertex)
{
    vertices.push_back(vertex);
}

void WireframeModelBuilder::addEdge(size_t index1, size_t index2)
{
    edges.push_back({ index1, index2 });
}

WireframeModel* WireframeModelBuilder::getResult()
{
    LOG_FUNC;

    WireframeModel* result = new WireframeModel(vertices.begin(), vertices.end(), edges.begin(), edges.end());
    vertices.clear();
    edges.clear();
    return result;
}
