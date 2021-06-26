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

void CameraAdapter::accept(IObjectVisitor& visitor)
{
    visitor.visit(*this);
}
