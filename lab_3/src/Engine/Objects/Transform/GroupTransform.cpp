#include "Objects/ObjectGroup.hpp"
#include "GroupTransform.hpp"


GroupTransform::GroupTransform(ObjectGroup& group)
    : group(group), scale(1, 1, 1)
{
}

const Vector& GroupTransform::getPosition() const
{
    return position;
}

const Vector& GroupTransform::getRotation() const
{
    return rotation;
}

const Vector& GroupTransform::getScale() const
{
    return scale;
}

void GroupTransform::setPosition(const Vector& pos)
{
    Vector delta = pos - position;

    for (auto& object : group)
    {
        auto& t = object->getTransform();
        t.setPosition(t.getPosition() + delta);
    }

    position = pos;
}

void GroupTransform::setRotation(const Vector& rot)
{
    Vector delta = rot - rotation;

    for (auto& object : group)
    {
        auto& t = object->getTransform();
        t.setRotation(t.getRotation() + delta);
    }

    rotation = rot;
}

void GroupTransform::setScale(const Vector& scl)
{
    Vector delta = scl - scale;

    for (auto& object : group)
    {
        auto& t = object->getTransform();
        t.setScale(t.getScale() + delta);
    }

    scale = scl;
}
