#pragma once

#include "Vertex.hpp"


class Edge
{
public:
    constexpr Edge(Vertex& v1, Vertex& v2) noexcept
        : startVertex(v1), endVertex(v2) {}

    inline Vertex& getStartVertex() noexcept { return startVertex; }
    inline Vertex& getEndVertex() noexcept { return endVertex; }

    inline Edge swap() noexcept { return Edge(endVertex, startVertex); }

private:
    Vertex& startVertex;
    Vertex& endVertex;
};
