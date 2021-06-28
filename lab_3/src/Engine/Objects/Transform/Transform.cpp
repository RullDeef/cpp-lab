#include <cmath>
#include "Transform.hpp"


Transform::Transform()
    : scale(1, 1, 1)
{
}

const Vector& Transform::getPosition() const
{
    return position;
}

const Vector& Transform::getRotation() const
{
    return rotation;
}

const Vector& Transform::getScale() const
{
    return scale;
}

void Transform::setPosition(const Vector& pos)
{
    position = pos;
}

void Transform::setRotation(const Vector& rot)
{
    rotation = rot;
}

void Transform::setScale(const Vector& scl)
{
    scale = scl;
}

Transform::operator Matrix() const
{
    auto T = Matrix::translation(position);
    auto R = Matrix::rotation(rotation);
    auto S = Matrix::scaling(scale);
    return T * R * S;
}
