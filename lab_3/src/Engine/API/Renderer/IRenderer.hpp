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

    virtual void beginFrame(std::shared_ptr<ICamera> camera);
    virtual void endFrame();

    void saveMatrix();
    void restoreMatrix();
    void multiplyMatrix(const Matrix& mat);

    virtual void setStrokeColor(const Color& color) = 0;

    virtual void drawLine(const Vector& p1, const Vector& p2) = 0;

    virtual void clear(const Color& color) = 0;

    virtual Rect getViewport() const = 0;
    virtual std::shared_ptr<ICamera> getCamera() const;

protected:
    const Matrix& getMatrix() const;

private:
    std::shared_ptr<ICamera> camera;
    std::stack<Matrix> matrixStack;
};
