#pragma once

#include <memory>
#include <list>
#include "IObject.hpp"
#include "Transform/GroupTransform.hpp"


class ObjectGroup : public IObject
{
public:
    using ObjectIterator = std::list<std::shared_ptr<IObject>>::iterator;
    using ConstObjectIterator = std::list<std::shared_ptr<IObject>>::const_iterator;

    explicit ObjectGroup(bool isOwner = true);
    explicit ObjectGroup(const std::string& name, bool isOwner = true);

    virtual ~ObjectGroup();

    virtual Transform& getTransform() override;
    virtual const Transform& getTransform() const override;

    void accept(IObjectVisitor& visitor) override;

    void insert(ObjectIterator iter, std::shared_ptr<IObject> object);

    void erase(ConstObjectIterator iter);
    void erase(ConstObjectIterator iterFirst, ConstObjectIterator iterLast);

    ObjectIterator begin();
    ObjectIterator end();

    ConstObjectIterator begin() const;
    ConstObjectIterator end() const;

private:
    GroupTransform* transform;
    std::list<std::shared_ptr<IObject>> objects;
    const bool isOwner;
};
