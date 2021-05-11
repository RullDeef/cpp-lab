#pragma once

#include <memory>
#include <stack>
#include "Engine/Core/Color.hpp"
#include "Engine/Core/Math/Rect.hpp"
#include "Engine/Core/Math/Vector.hpp"
#include "Engine/Core/Math/Matrix.hpp"

class ICamera;

class IRenderer
{
public:
    IRenderer();
    virtual ~IRenderer() = default;

    virtual void beginFrame(std::shared_ptr<ICamera> camera) = 0;
    virtual void endFrame() = 0;

    void saveMatrix();
    void restoreMatrix();
    void multiplyMatrix(const Matrix& mat);

    virtual void setStrokeColor(const Color& color) = 0;

    virtual void drawLine(const Vector& p1, const Vector& p2) = 0;

    virtual void clear(const Color& color) = 0;

    virtual Rect getViewport() const = 0;

protected:
    const Matrix& getMatrix() const;

private:
    std::stack<Matrix> matrixStack;
};
