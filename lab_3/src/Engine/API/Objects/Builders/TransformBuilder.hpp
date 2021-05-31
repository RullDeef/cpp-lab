#pragma once

#include "Engine/Core/Math/Vector.hpp"
#include "Engine/Core/Math/Transform.hpp"


class TransformBuilder
{
public:
    TransformBuilder& translate(const Vector& offset);
    TransformBuilder& scale(const Vector& factor);
    TransformBuilder& rotate(const Vector& axis, double angle);

    Transform build();

private:
    Transform transform;
};
