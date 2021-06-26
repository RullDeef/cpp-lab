#pragma once

#include "IManager.hpp"
#include "Core/Math/Transform.hpp"


class TransformManager : public IManager
{
public:
    virtual ~TransformManager() = default;

    virtual void transform(const Transform& t) {}
};
