#pragma once

#include <string>
#include <list>
#include <memory>
#include "Core/Math/Transform.hpp"

class IObjectVisitor;


class ISceneObject
{
public:
    using ISceneObjectIterator = std::list<std::shared_ptr<ISceneObject>>::iterator;
    using ISceneObjectConstIterator = std::list<std::shared_ptr<ISceneObject>>::const_iterator;

    explicit ISceneObject(const std::string& name = "");
    virtual ~ISceneObject() = default;

    const std::string& getName() const noexcept;
    void setName(const std::string& name);

    Transform& getTransform();
    const Transform& getTransform() const;

    virtual std::shared_ptr<ISceneObject> clone() const = 0;

    virtual void accept(IObjectVisitor* visitor) {}

    virtual void addChild(std::shared_ptr<ISceneObject> object) {}
    virtual void removeChild(std::shared_ptr<ISceneObject> object) {}

    virtual bool isComposite() const;
    virtual bool isVisible() const = 0;

    virtual ISceneObjectIterator begin() = 0;
    virtual ISceneObjectIterator end() = 0;
    virtual ISceneObjectConstIterator begin() const = 0;
    virtual ISceneObjectConstIterator end() const = 0;

private:
    std::string name;
    Transform transform;
};
