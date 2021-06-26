#include "ICamera.hpp"
#include "Utils/Logger.hpp"


void ICamera::setViewport(Rect viewport)
{
    this->viewport = viewport;
}

Rect ICamera::getViewport() const
{
    return viewport;
}

Vector ICamera::projectPoint(const Vector& point) const
{
    Vector res = point * _vp;

    res.setX(res.getX() / res.getZ() + viewport.getWidth() / 2);
    res.setY(viewport.getHeight() / 2 - res.getY() / res.getZ());

    return res;
}

void ICamera::setViewMatrix(const Matrix& matrix)
{
    viewMatrix = matrix.inverse();

    _vp = viewMatrix * projectionMatrix;
}

const Matrix& ICamera::getViewMatrix() const
{
    return viewMatrix;
}

const Matrix& ICamera::getProjectionMatrix() const
{
    return projectionMatrix;
}

void ICamera::setProjectionMatrix(const Matrix& matrix)
{
    projectionMatrix = matrix;

    _vp = viewMatrix * projectionMatrix;
}
