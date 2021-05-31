#pragma once

#include <string>
#include <list>
#include <memory>
#include "Core/Math/Transform.hpp"

class IObjectVisitor;
class Memento;


class ISceneObject
{
public:
    using ISceneObjectIterator = std::list<std::shared_ptr<ISceneObject>>::iterator;
    using ISceneObjectConstIterator = std::list<std::shared_ptr<ISceneObject>>::const_iterator;

    ISceneObject(const std::string& name = "");

    const std::string& getName() const;
    void setName(const std::string& name);

    virtual void applyTransform(const Transform& t) {};
    virtual std::shared_ptr<ISceneObject> clone() const = 0;

    virtual void accept(std::shared_ptr<IObjectVisitor> visitor) {};

    virtual void addChild(std::shared_ptr<ISceneObject> object) {}
    virtual void removeChild(std::shared_ptr<ISceneObject> object) {}

    virtual bool isComposite() const { return false; }
    virtual bool isVisible() const = 0;

    virtual std::shared_ptr<Memento> saveState() = 0;
    virtual void restoreState(std::shared_ptr<Memento> memento) = 0;

    virtual ISceneObjectIterator begin() = 0;
    virtual ISceneObjectIterator end() = 0;
    virtual ISceneObjectConstIterator begin() const = 0;
    virtual ISceneObjectConstIterator end() const = 0;

private:
    std::string name;
};
