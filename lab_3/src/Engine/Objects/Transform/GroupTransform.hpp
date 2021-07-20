#pragma once

#include "Transform.hpp"

class ObjectGroup;


class GroupTransform : public Transform
{
public:
    GroupTransform(ObjectGroup& group);

    virtual const Vector& getPosition() const override;
    virtual const Vector& getRotation() const override;
    virtual const Vector& getScale() const override;

    virtual void setPosition(const Vector& pos) override;
    virtual void setRotation(const Vector& rot) override;
    virtual void setScale(const Vector& scl) override;

private:
    ObjectGroup& group;

    mutable Vector position;
    mutable Vector rotation;
    mutable Vector scale;
};
