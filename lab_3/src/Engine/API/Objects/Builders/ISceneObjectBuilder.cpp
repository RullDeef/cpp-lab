#include "ISceneObjectBuilder.hpp"

void ISceneObjectBuilder::setName(const std::string& name)
{
    this->name = name;
}

void ISceneObjectBuilder::setTransform(const Transform& t)
{
    transform = t;
}

const std::string& ISceneObjectBuilder::getName() const
{
    return name;
}

const Transform& ISceneObjectBuilder::getTransform() const
{
    return transform;
}
