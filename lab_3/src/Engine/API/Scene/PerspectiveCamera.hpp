#pragma once

#include "ICamera.hpp"
#include "Math/Rect.hpp"

class PerspectiveCamera : public ICamera
{
public:
    void setViewport(Rect viewport);
    void setFov(double fov);
    void setNear(double near);
    void setFar(double far);

private:
    void updateProjectionMatrix();

    double fov;
    double near;
    double far;
};
