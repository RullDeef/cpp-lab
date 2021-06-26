#include "ISceneObject.hpp"


ISceneObject::ISceneObject(const std::string& name)
    : name(name)
{
}

const std::string& ISceneObject::getName() const noexcept
{
    return name;
}

void ISceneObject::setName(const std::string& name)
{
    this->name = name;
}

Transform& ISceneObject::getTransform()
{
    return transform;
}

const Transform& ISceneObject::getTransform() const
{
    return transform;
}

bool ISceneObject::isComposite() const
{
    return false;
}
