#pragma once

#include <list>
#include "IObject.hpp"


class ObjectGroup : public IObject
{
    using ObjectIterator = std::list<IObject*>::iterator;
    using ConstObjectIterator = std::list<IObject*>::const_iterator;

public:
    ObjectGroup() = default;
    explicit ObjectGroup(const std::string& name);

    ~ObjectGroup();

    void accept(IObjectVisitor& visitor) override;

    ObjectIterator begin();
    ObjectIterator end();

    ConstObjectIterator begin() const;
    ConstObjectIterator end() const;

private:
    std::list<IObject*> objects;
};
