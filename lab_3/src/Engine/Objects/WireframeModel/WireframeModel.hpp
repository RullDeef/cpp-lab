#pragma once

#include <vector>
#include "Core/Vertex.hpp"


class WireframeModel
{
    using Edge = std::pair<size_t, size_t>;

public:
    WireframeModel() = default;

    template<typename _VertexInputIt, typename _EdgeInputIt>
    WireframeModel(_VertexInputIt vertBegin, _VertexInputIt vertEnd, _EdgeInputIt edgeBegin, _EdgeInputIt edgeEnd)
        : vertices(vertBegin, vertEnd), edges(edgeBegin, edgeEnd) {} // TODO: сделать проверку на корректность индексов ребер

    const std::vector<Vertex>& getVertices() const;
    const std::vector<Edge>& getEdges() const;

private:
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
};
