#pragma once

#include "Math/Vector.hpp"
#include "Math/Rect.hpp"
#include "ISceneObject.hpp"

class ICamera : public ISceneObject
{
public:
    void setViewport(Rect viewport);
    Rect getViewport() const;

    Vector projectPoint(const Vector& point) const;

    virtual void draw(std::shared_ptr<IRenderer> renderer) const override {}

protected:
    ICamera() = default;

    void setProjectionMatrix(const Matrix& matrix);

private:
    Rect viewport;
    Matrix projectionMatrix = Matrix::identity();
};
