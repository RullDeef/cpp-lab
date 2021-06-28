#pragma once

#include "IManager.hpp"
#include "Core/Math/Vector.hpp"

class IObject;


class TransformManager : public IManager
{
public:
    void translateObject(IObject* object, const Vector& offset);
    void rotateObject(IObject* object, const Vector& angles);
    void scaleObject(IObject* object, const Vector& factor);
};
