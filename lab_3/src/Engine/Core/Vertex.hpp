#pragma once

#include "Core/Math/Vector.hpp"


class Vertex
{
public:
    explicit Vertex(const Vector& position);

    const Vector& getPosition() const;

private:
    Vector position;
};
