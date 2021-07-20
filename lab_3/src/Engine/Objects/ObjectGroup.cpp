#include "Visitors/IObjectVisitor.hpp"
#include "ObjectGroup.hpp"


ObjectGroup::ObjectGroup(bool isOwner)
    : isOwner(isOwner)
{
    transform = new GroupTransform(*this);
}

ObjectGroup::ObjectGroup(const std::string& name, bool isOwner)
    : IObject(name), isOwner(isOwner)
{
    transform = new GroupTransform(*this);
}

ObjectGroup::~ObjectGroup()
{
    if (isOwner)
        for (auto& object : objects)
            delete object;

    delete transform;
}

Transform& ObjectGroup::getTransform()
{
    return *transform;
}

const Transform& ObjectGroup::getTransform() const
{
    return *transform;
}

void ObjectGroup::accept(IObjectVisitor& visitor)
{
    visitor.visit(*this);
}

void ObjectGroup::insert(ObjectIterator iter, std::shared_ptr<IObject> object)
{
    objects.insert(iter, object);
}

void ObjectGroup::erase(ConstObjectIterator iter)
{
    if (isOwner)
        delete *iter;

    objects.erase(iter);
}

void ObjectGroup::erase(ConstObjectIterator iterFirst, ConstObjectIterator iterLast)
{
    if (isOwner)
        for (auto iter = iterFirst; iter != iterLast; ++iter)
            delete *iter;

    objects.erase(iterFirst, iterLast);
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
