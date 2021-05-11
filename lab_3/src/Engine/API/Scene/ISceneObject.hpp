#pragma once

#include "Math/Transform.hpp"
#include "Renderer/IDrawable.hpp"

class ISceneObject : public IDrawable
{
public:
    ISceneObject() = default;

    Transform& getTransform();
    const Transform& getTransform() const;

    void setTransform(const Transform& t);

private:
    Transform transform;
};
