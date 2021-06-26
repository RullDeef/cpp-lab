#include "DefaultCameraBuilder.hpp"
#include "API/Objects/Camera/PerspectiveCamera.hpp"


void DefaultCameraBuilder::setFov(double angle)
{
    this->angle = angle;
}

void DefaultCameraBuilder::setViewport(Rect viewport)
{
    this->viewport = viewport;
}

void DefaultCameraBuilder::setNear(double near)
{
    this->near = near;
}

void DefaultCameraBuilder::setFar(double far)
{
    this->far = far;
}

std::shared_ptr<ISceneObject> DefaultCameraBuilder::build()
{
    std::shared_ptr<ICamera> camera = std::make_shared<PerspectiveCamera>();
    std::shared_ptr<ISceneObject> object = std::shared_ptr<ISceneObject>(new CameraAdapter(camera));

    object->setName(getName());
    object->getTransform() = getTransform();

    return object;
}
