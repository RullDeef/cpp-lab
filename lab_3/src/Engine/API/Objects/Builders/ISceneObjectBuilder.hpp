#pragma once

#include "API/Objects/ISceneObject.hpp"


class ISceneObjectBuilder
{
public:
    virtual ~ISceneObjectBuilder() = default;

    virtual std::shared_ptr<ISceneObject> build(const Transform& t = Transform()) = 0;
};
