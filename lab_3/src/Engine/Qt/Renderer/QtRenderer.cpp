#include "QtRenderer.hpp"
#include "API/Objects/ICamera.hpp"
#include "Utils/Logger.hpp"


QtRenderer::QtRenderer(QGraphicsView* graphicsView)
    : graphics(graphicsView), graphicsScene(new QGraphicsScene(graphicsView))
{
    graphics->setScene(graphicsScene);
}

QtRenderer::~QtRenderer()
{
}

void QtRenderer::setStrokeColor(const Color& color)
{
    strokeColor = color;
}

void QtRenderer::drawLine(const Vector& p1, const Vector& p2)
{
    Vector pp1 = getCamera()->projectPoint(p1 * getMatrix());
    Vector pp2 = getCamera()->projectPoint(p2 * getMatrix());

    QPen pen(strokeColor.getHex());

    graphicsScene->addLine(pp1.getX(), pp1.getY(), pp2.getX(), pp2.getY(), pen);
}

void QtRenderer::clear(const Color& color)
{
    graphicsScene->clear();
    graphics->update();
}

Rect QtRenderer::getViewport() const
{
    double width = graphics->viewport()->width();
    double height = graphics->viewport()->height();

    return Rect(0.0, 0.0, width, height);
}
