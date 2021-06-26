#include <stdexcept>
#include "API/Objects/IObjectVisitor.hpp"
#include "CameraAdapter.hpp"


CameraAdapter::CameraAdapter(std::shared_ptr<ICamera> camera)
    : camera(camera)
{
}

std::shared_ptr<ISceneObject> CameraAdapter::clone() const
{
    throw std::runtime_error("not implemented");
}

void CameraAdapter::accept(IObjectVisitor* visitor)
{
    visitor->visit(*this);
}

bool CameraAdapter::isVisible() const
{
    return false;
}

std::shared_ptr<ICamera> CameraAdapter::getCamera()
{
    return camera;
}

std::shared_ptr<Memento> CameraAdapter::saveState()
{
    throw std::runtime_error("not implemented");
}

void CameraAdapter::restoreState(std::shared_ptr<Memento> memento)
{
    throw std::runtime_error("not implemented");
}

ISceneObject::ISceneObjectIterator CameraAdapter::begin()
{
    throw std::runtime_error("not implemented");
}

ISceneObject::ISceneObjectIterator CameraAdapter::end()
{
    throw std::runtime_error("not implemented");
}

ISceneObject::ISceneObjectConstIterator CameraAdapter::begin() const
{
    throw std::runtime_error("not implemented");
}

ISceneObject::ISceneObjectConstIterator CameraAdapter::end() const
{
    throw std::runtime_error("not implemented");
}
