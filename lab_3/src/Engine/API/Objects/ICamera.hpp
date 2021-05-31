#pragma once

#include <memory>
#include "Core/Math/Vector.hpp"
#include "Core/Math/Rect.hpp"
#include "Core/Math/Matrix.hpp"
#include "ISceneObject.hpp"


class ICamera : public ISceneObject
{
public:
    void setViewport(Rect viewport);
    Rect getViewport() const;

    Vector projectPoint(const Vector& point) const;

    // virtual void draw(std::shared_ptr<IRenderer> renderer) const override {}

protected:
    ICamera() = default;

    void setProjectionMatrix(const Matrix& matrix);

private:
    Rect viewport;
    Matrix projectionMatrix = Matrix::identity();
};
