#include "RenderViewport.hpp"
#include <QPainter>
#include <QMouseEvent>


RenderViewport::RenderViewport()
    : renderTarget(QPixmap(1, 1).toImage())
{
    setMouseTracking(true);
    renderTarget.fill(Qt::white);
}

QImage& RenderViewport::getRenderTarget()
{
    return renderTarget;
}

void RenderViewport::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, renderTarget);
}

void RenderViewport::resizeEvent(QResizeEvent* event)
{
    QImage oldRenderTarget = renderTarget;
    renderTarget = QPixmap(size()).toImage();
    renderTarget.fill(Qt::white);

    QPainter painter(&renderTarget);
    int x = 0.5 * (width() - oldRenderTarget.width());
    int y = 0.5 * (height() - oldRenderTarget.height());
    painter.drawImage(x, y, oldRenderTarget);
}

void RenderViewport::mouseMoveEvent(QMouseEvent* event)
{
    emit mouseMoveSignal(event);
}

void RenderViewport::mousePressEvent(QMouseEvent* event)
{
    emit mousePressSignal(event);
}

void RenderViewport::mouseReleaseEvent(QMouseEvent* event)
{
    emit mouseReleaseSignal(event);
}
