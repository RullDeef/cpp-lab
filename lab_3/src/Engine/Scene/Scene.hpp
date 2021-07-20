#pragma once

#include <memory>
#include <list>

class IObject;


class Scene
{
    using ObjectIterator = std::list<std::shared_ptr<IObject>>::iterator;
    using ConstObjectIterator = std::list<std::shared_ptr<IObject>>::const_iterator;

public:
    Scene() = default;

    template<typename _InputIt>
    Scene(_InputIt iterBegin, _InputIt iterEnd)
        : objects(iterBegin, iterEnd) {}

    void insert(ObjectIterator iter, std::shared_ptr<IObject> object);

    void erase(ConstObjectIterator iter);
    void erase(ConstObjectIterator iterFirst, ConstObjectIterator iterLast);

    ObjectIterator begin();
    ObjectIterator end();

    ConstObjectIterator begin() const;
    ConstObjectIterator end() const;

private:
    std::list<std::shared_ptr<IObject>> objects;
};
