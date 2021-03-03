#pragma once

#include <QtWidgets/QMainWindow>
#include <QPainter>
#include <QTimer>
#include "ui_modelviewer.h"
#include "../core/model_viewer.hpp"

// одна точка входа.
// свои модули для математики.
// "слишком умный интерфейс".
// не использовать STL.
// только перенос/поворот/масштабирование.

namespace ui
{
    class ModelViewer : public QMainWindow
    {
        Q_OBJECT

    public:
        ModelViewer(QWidget *parent = Q_NULLPTR);
        ~ModelViewer();

    protected:
        void paintEvent(QPaintEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void wheelEvent(QWheelEvent* event);

        void paintProjection(const core::ProjectedModel& prj);
        void paintModel();

    private:
        bool handleErrorCode(core::ErrorCode status);

    public slots:
        void loadModelSlot();
        void saveModelSlot();

    private:
        Ui::ModelViewer ui;

        bool model_loaded;
        core::Context context;

        bool grabbing;
        bool rotating;
        QPointF prev_mouse_pos;

        QPainter painter;

        QPen pen;
    };
}
