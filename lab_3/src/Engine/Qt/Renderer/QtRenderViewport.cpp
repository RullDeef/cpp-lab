#include "QtRenderViewport.hpp"
#include <QPainter>
#include <QMouseEvent>


QtRenderViewport::QtRenderViewport()
    : renderTarget(QPixmap(1, 1).toImage())
{
    setMouseTracking(true);
    renderTarget.fill(Qt::white);
}

void QtRenderViewport::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, renderTarget);
}

Rect QtRenderViewport::getViewportRect() const
{
    return Rect(0, 0, width(), height());
}

void QtRenderViewport::clear()
{
    renderTarget.fill(Qt::white);
}

void QtRenderViewport::drawLine(int x1, int y1, int x2, int y2)
{
    QPainter painter(&renderTarget);
    painter.drawLine(x1, y1, x2, y2);
}

void QtRenderViewport::resizeEvent(QResizeEvent* event)
{
    QImage oldRenderTarget = renderTarget;
    renderTarget = QPixmap(size()).toImage();
    renderTarget.fill(Qt::white);

    QPainter painter(&renderTarget);
    int x = 0.5 * (width() - oldRenderTarget.width());
    int y = 0.5 * (height() - oldRenderTarget.height());
    painter.drawImage(x, y, oldRenderTarget);
}

void QtRenderViewport::mouseMoveEvent(QMouseEvent* event)
{
    emit mouseMoveSignal(event);
}

void QtRenderViewport::mousePressEvent(QMouseEvent* event)
{
    emit mousePressSignal(event);
}

void QtRenderViewport::mouseReleaseEvent(QMouseEvent* event)
{
    emit mouseReleaseSignal(event);
}
