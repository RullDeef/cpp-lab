#include "WireframeModel.hpp"

const std::vector<Vertex>& WireframeModel::getVertices() const
{
    return vertices;
}

const std::vector<WireframeModel::Edge>& WireframeModel::getEdges() const
{
    return edges;
}
