#pragma once

#include <memory>
#include <stack>
#include <QWidget>
#include <QPainter>
#include "Core/Color.hpp"
#include "Core/Math/Rect.hpp"
#include "Core/Math/Matrix.hpp"
#include "API/Renderer/IRenderer.hpp"
#include "RenderViewport.hpp"


class QtRenderer : public IRenderer
{
public:
    QtRenderer(RenderViewport* viewport);
    virtual ~QtRenderer() = default;

    void beginFrame(ICamera* camera) override;
    void endFrame() override;

    virtual void visit(SceneObjectGroup& objectGroup) override;
    virtual void visit(HullModelAdapter& hullModelAdapter) override;
    virtual void visit(CameraAdapter& camera) override;

    virtual Rect getViewport() override;

protected:
    void setStrokeColor(const Color& color);
    void drawLine(const Vector& p1, const Vector& p2);
    void clear(const Color& color);

    const Matrix& getMatrix() const;

private:
    ICamera* camera = nullptr;
    std::stack<Matrix> matrixStack;

    RenderViewport* renderViewport;
    QPainter* painter;

    Color strokeColor;
};
