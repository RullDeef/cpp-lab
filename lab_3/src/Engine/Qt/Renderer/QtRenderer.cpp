#include "QtRenderer.hpp"
#include "Utils/Logger.hpp"
#include "API/Scene/Scene.hpp"
#include "API/Objects/Camera/ICamera.hpp"
#include "API/Objects/Camera/CameraAdapter.hpp"
#include "API/Objects/HullModel/Edge.hpp"
#include "API/Objects/HullModel/HullModelAdapter.hpp"


QtRenderer::QtRenderer(RenderViewport* viewport)
    : renderViewport(viewport), painter(nullptr)
{
}

void QtRenderer::beginFrame(ICamera* camera)
{
    this->camera = camera;
    painter = new QPainter(&renderViewport->getRenderTarget());
    clear(Color(255, 255, 255, 255));

    matrixStack = {};
    matrixStack.push(Matrix::identity());
}

void QtRenderer::endFrame()
{
    camera = nullptr;
    delete painter;
    painter = nullptr;
}

void QtRenderer::visit(SceneObjectGroup& objectGroup)
{
    matrixStack.push(objectGroup.getTransform() * getMatrix());

    for (auto& obj : objectGroup)
        obj->accept(this);

    matrixStack.pop();
}

void QtRenderer::visit(HullModelAdapter& hullModelAdapter)
{
    matrixStack.push(hullModelAdapter.getTransform() * getMatrix());

    for (auto& edge : hullModelAdapter.getModel()->getEdges())
        drawLine(edge.getStartVertex(), edge.getEndVertex());

    matrixStack.pop();
}

void QtRenderer::visit(CameraAdapter& camera)
{
}

void QtRenderer::setStrokeColor(const Color& color)
{
    strokeColor = color;
}

void QtRenderer::drawLine(const Vector& p1, const Vector& p2)
{
    Vector pp1 = camera->projectPoint(p1 * getMatrix());
    Vector pp2 = camera->projectPoint(p2 * getMatrix());

    QPen pen(strokeColor.getHex());

    painter->setPen(pen);
    painter->drawLine(pp1.getX(), pp1.getY(), pp2.getX(), pp2.getY());
}

void QtRenderer::clear(const Color& color)
{
    painter->fillRect(renderViewport->rect(), color.getHex());
}

Rect QtRenderer::getViewport()
{
    double width = renderViewport->width();
    double height = renderViewport->height();

    return Rect(0.0, 0.0, width, height);
}

const Matrix& QtRenderer::getMatrix() const
{
    return matrixStack.top();
}
