#pragma once

#include <QWidget>
#include <QImage>


class RenderViewport : public QWidget
{
    Q_OBJECT

public:
    RenderViewport();
    virtual ~RenderViewport() = default;

    QImage& getRenderTarget();

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
