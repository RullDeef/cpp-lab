#include <algorithm>
#include "PerspectiveCamera.hpp"
#include "Core/Math/Matrix.hpp"


void PerspectiveCamera::setViewport(Rect viewport)
{
    ICamera::setViewport(viewport);
    updateProjectionMatrix();
}

void PerspectiveCamera::setFov(double fov)
{
    this->fov = fov;
    updateProjectionMatrix();
}

void PerspectiveCamera::setNear(double near)
{
    this->near = near;
    updateProjectionMatrix();
}

void PerspectiveCamera::setFar(double far)
{
    this->far = far;
    updateProjectionMatrix();
}

void PerspectiveCamera::updateProjectionMatrix()
{
    Rect viewport = getViewport();
    double aspect = viewport.getAspect();
    Matrix matrix = Matrix::perspective(fov, 1.0, near, far);
    double scaleFactor = std::min(viewport.getWidth(), viewport.getHeight());
    matrix.scale({ scaleFactor, scaleFactor, 1.0 });
    setProjectionMatrix(matrix);
}
