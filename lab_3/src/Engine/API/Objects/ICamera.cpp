#include "ICamera.hpp"
#include "Core/Math/Matrix.hpp"
#include "Engine/Utils/Logger.hpp"

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
    Vector res = point;// *(getTransform().inverse() * projectionMatrix);

    res.setX(res.getX() / res.getZ());
    res.setY(res.getY() / res.getZ());

    return res;
}

void ICamera::setProjectionMatrix(const Matrix& matrix)
{
    projectionMatrix = matrix;
}
