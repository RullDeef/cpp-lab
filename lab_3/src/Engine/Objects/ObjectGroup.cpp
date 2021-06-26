#include "Visitors/IObjectVisitor.hpp"
#include "ObjectGroup.hpp"


ObjectGroup::ObjectGroup(const std::string& name)
    : IObject(name)
{
}

ObjectGroup::~ObjectGroup()
{
    for (auto& object : objects)
        delete object;
}

void ObjectGroup::accept(IObjectVisitor& visitor)
{
    visitor.visit(*this);
}

ObjectGroup::ObjectIterator ObjectGroup::begin()
{
    return objects.begin();
}

ObjectGroup::ObjectIterator ObjectGroup::end()
{
    return objects.end();
}

ObjectGroup::ConstObjectIterator ObjectGroup::begin() const
{
    return objects.begin();
}

ObjectGroup::ConstObjectIterator ObjectGroup::end() const
{
    return objects.end();
}
