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
