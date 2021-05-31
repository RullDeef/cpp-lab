#include "TransformBuilder.hpp"

TransformBuilder& TransformBuilder::translate(const Vector& offset)
{
    transform.translate(offset);
    return *this;
}

TransformBuilder& TransformBuilder::scale(const Vector& factor)
{
    transform.scale(factor);
    return *this;
}

TransformBuilder& TransformBuilder::rotate(const Vector& axis, double angle)
{
    transform.rotate(axis, angle);
    return *this;
}

Transform TransformBuilder::build()
{
    return transform;
}
