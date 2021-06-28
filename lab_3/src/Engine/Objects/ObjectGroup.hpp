#pragma once

#include <list>
#include "IObject.hpp"


class ObjectGroup : public IObject
{
public:
    using ObjectIterator = std::list<IObject*>::iterator;
    using ConstObjectIterator = std::list<IObject*>::const_iterator;

    explicit ObjectGroup(bool isOwner = true);
    explicit ObjectGroup(const std::string& name, bool isOwner = true);

    virtual ~ObjectGroup();

    void accept(IObjectVisitor& visitor) override;

    void insert(ObjectIterator iter, IObject* object);

    void erase(ConstObjectIterator iter);
    void erase(ConstObjectIterator iterFirst, ConstObjectIterator iterLast);

    ObjectIterator begin();
    ObjectIterator end();

    ConstObjectIterator begin() const;
    ConstObjectIterator end() const;

private:
    std::list<IObject*> objects;
    const bool isOwner;
};
