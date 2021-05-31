#include "ISceneObject.hpp"


ISceneObject::ISceneObject(const std::string& name)
    : name(name)
{
}

const std::string& ISceneObject::getName() const
{
    return name;
}

void ISceneObject::setName(const std::string& name)
{
    this->name = name;
}
