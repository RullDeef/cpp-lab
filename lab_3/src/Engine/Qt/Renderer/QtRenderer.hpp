#pragma once

#include <memory>
#include <stack>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "../../Core/Color.hpp"
#include "Engine/Core/Math/Matrix.hpp"
#include "../../API/Renderer/IRenderer.hpp"


class QtRenderer : public IRenderer
{
public:
    QtRenderer(QGraphicsView* graphicsView);
    virtual ~QtRenderer();

    virtual void setStrokeColor(const Color& color) override;

    virtual void drawLine(const Vector& p1, const Vector& p2) override;

    virtual void clear(const Color& color) override;

    virtual Rect getViewport() const override;

private:
    QGraphicsView* graphics;
    QGraphicsScene* graphicsScene;

    Color strokeColor;
};
