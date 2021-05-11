#include "PerspectiveCamera.hpp"

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
    Matrix matrix = Matrix::perspective(fov, aspect, near, far);
    matrix.scale({ viewport.getWidth(), viewport.getWidth(), 1.0 });
    setProjectionMatrix(matrix);
}
