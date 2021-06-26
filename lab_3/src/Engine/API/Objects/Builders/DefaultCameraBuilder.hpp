#pragma once

#include "API/Objects/Camera/CameraAdapter.hpp"
#include "ISceneObjectBuilder.hpp"


class DefaultCameraBuilder : public ISceneObjectBuilder
{
public:
    void setFov(double angle);
    void setViewport(Rect viewport);
    void setNear(double near);
    void setFar(double far);

    virtual std::shared_ptr<ISceneObject> build() override;

private:
    Rect viewport;
    double angle = 75.0 * 3.1415 / 180.0;
    double near = 0.01;
    double far = 1000.0;
};
