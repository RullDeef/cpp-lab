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

    const Vector& getPosition() const;
    const Vector& getRotation() const;
    const Vector& getScale() const;

    void setPosition(const Vector& pos);
    void setRotation(const Vector& rot);
    void setScale(const Vector& scl);

    operator Matrix() const;

private:
    Vector position;
    Vector rotation;
    Vector scale;
};
