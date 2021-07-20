#pragma once

#include "Core/Math/Vector.hpp"
#include "Core/Math/Matrix.hpp"


class Transform
{
public:
    Transform();
    Transform(const Transform& t) = delete;
    Transform(Transform&& t) = delete;

    // Transform& operator=(const Transform& t) = delete;

    virtual const Vector& getPosition() const;
    virtual const Vector& getRotation() const;
    virtual const Vector& getScale() const;

    virtual void setPosition(const Vector& pos);
    virtual void setRotation(const Vector& rot);
    virtual void setScale(const Vector& scl);

    operator Matrix() const;

private:
    Vector position;
    Vector rotation;
    Vector scale;
};
