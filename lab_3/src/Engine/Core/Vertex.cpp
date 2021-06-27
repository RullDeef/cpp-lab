#include "Vertex.hpp"

Vertex::Vertex(const Vector& position)
    : position(position)
{
}

const Vector& Vertex::getPosition() const
{
    return position;
}
