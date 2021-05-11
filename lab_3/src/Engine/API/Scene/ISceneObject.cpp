#include "ISceneObject.hpp"

Transform& ISceneObject::getTransform()
{
    return transform;
}

const Transform& ISceneObject::getTransform() const
{
    return transform;
}

void ISceneObject::setTransform(const Transform& t)
{
    transform = t;
}
