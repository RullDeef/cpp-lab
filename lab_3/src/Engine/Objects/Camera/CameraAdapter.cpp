#include <stdexcept>
#include "CameraAdapter.hpp"
#include "Visitors/IObjectVisitor.hpp"


CameraAdapter::CameraAdapter(const std::string& name, Camera* camera)
    : IObject(name), camera(camera)
{
}

CameraAdapter::CameraAdapter(Camera* camera)
    : camera(camera)
{
}

CameraAdapter::~CameraAdapter()
{
    if (camera)
        delete camera;
}

Camera& CameraAdapter::getCamera()
{
    if (!camera)
        throw std::runtime_error("CameraAdapter: bad camera pointer");
    return *camera;
}

const Camera& CameraAdapter::getCamera() const
{
    if (!camera)
        throw std::runtime_error("CameraAdapter: bad camera pointer");
    return *camera;
}

void CameraAdapter::accept(IObjectVisitor& visitor)
{
    visitor.visit(*this);
}
