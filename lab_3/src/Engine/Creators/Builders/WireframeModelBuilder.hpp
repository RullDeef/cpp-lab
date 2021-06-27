#pragma once

#include <list>
#include "Objects/WireframeModel/WireframeModel.hpp"


class WireframeModelBuilder
{
public:
    void addVertex(const Vertex& vertex);
    void addEdge(size_t index1, size_t index2);

    WireframeModel* getResult();

private:
    std::list<Vertex> vertices;
    std::list<WireframeModel::Edge> edges;
};
