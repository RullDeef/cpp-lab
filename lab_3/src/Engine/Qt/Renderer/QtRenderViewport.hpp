#pragma once

#include <QWidget>
#include <QImage>

#include "Visitors/Renderer/RenderViewport.hpp"


class QtRenderViewport : public QWidget, public RenderViewport
{
    Q_OBJECT

public:
    QtRenderViewport();

    Rect getViewportRect() const override;

    void clear() override;
    void drawLine(int x1, int y1, int x2, int y2) override;

signals:
    void mousePressSignal(QMouseEvent* event);
    void mouseMoveSignal(QMouseEvent* event);
    void mouseReleaseSignal(QMouseEvent* event);

protected slots:
    virtual void paintEvent(QPaintEvent* event) override;
    virtual void resizeEvent(QResizeEvent* event) override;

    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QImage renderTarget;
};
