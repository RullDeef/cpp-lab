#pragma once

#include <string>
#include "Transform/Transform.hpp"

class IObjectVisitor;


class IObject
{
public:
    explicit IObject(const std::string& name = "(unnamed)");
    virtual ~IObject() = default;

    const std::string& getName() const;
    void setName(const std::string& newName);

    virtual Transform& getTransform();
    virtual const Transform& getTransform() const;

    virtual void accept(IObjectVisitor& visitor) {};

private:
    std::string name;
    Transform transform;
};