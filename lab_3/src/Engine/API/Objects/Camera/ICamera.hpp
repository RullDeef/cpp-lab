#pragma once

#include "Core/Math/Vector.hpp"
#include "Core/Math/Rect.hpp"
#include "Core/Math/Matrix.hpp"


class ICamera
{
public:
    void setViewport(Rect viewport);
    Rect getViewport() const;

    Vector projectPoint(const Vector& point) const;

    void setViewMatrix(const Matrix& matrix);
    const Matrix& getViewMatrix() const;
    const Matrix& getProjectionMatrix() const;

protected:
    ICamera() = default;

    void setProjectionMatrix(const Matrix& matrix);

private:
    Rect viewport;

    Matrix projectionMatrix = Matrix::identity();
    Matrix viewMatrix = Matrix::identity();
    Matrix _vp;
};
