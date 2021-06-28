#include "IObject.hpp"

IObject::IObject(const std::string& name)
    : name(name)
{
}

const std::string& IObject::getName() const
{
    return name;
}

void IObject::setName(const std::string& newName)
{
    name = newName;
}

Transform& IObject::getTransform()
{
    return transform;
}

const Transform& IObject::getTransform() const
{
    return transform;
}
