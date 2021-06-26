#pragma once

#include <vector>
#include "Vertex.hpp"
#include "Edge.hpp"


class HullModel
{
public:
    HullModel() = default;
    HullModel(std::vector<Vertex> verts, std::vector<Edge> edges);

    inline const std::vector<Vertex>& getVertices() const noexcept { return vertices; }
    inline const std::vector<Edge>& getEdges() const noexcept { return edges; }

    inline std::vector<Vertex>& getVertices() noexcept { return vertices; }
    inline std::vector<Edge>& getEdges() noexcept { return edges; }

private:
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
};
