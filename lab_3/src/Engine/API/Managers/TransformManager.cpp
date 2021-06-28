#include <stdexcept>
#include "TransformManager.hpp"
#include "Objects/IObject.hpp"


void TransformManager::translateObject(IObject* object, const Vector& offset)
{
    if (!object)
        throw std::runtime_error("TransformManager::translateObject: bad object pointer");

    auto& t = object->getTransform();
    t.setPosition(t.getPosition() + offset);
}

void TransformManager::rotateObject(IObject* object, const Vector& angles)
{
    if (!object)
        throw std::runtime_error("TransformManager::rotateObject: bad object pointer");

    auto& t = object->getTransform();
    t.setRotation(t.getRotation() + angles);
}

void TransformManager::scaleObject(IObject* object, const Vector& factor)
{
    if (!object)
        throw std::runtime_error("TransformManager::scaleObject: bad object pointer");

    auto& t = object->getTransform();
    t.setScale(t.getScale() + factor);
}
