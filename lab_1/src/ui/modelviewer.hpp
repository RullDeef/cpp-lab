#pragma once

#include <QtWidgets/QMainWindow>
#include <QPainter>
#include <QTimer>
#include "ui_modelviewer.h"
#include "../core/model_viewer.hpp"

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
        bool requestFilename(std::string& filename);
        bool handleErrorCode(core::ErrorCode status);

    public slots:
        void loadModelSlot();
        void saveModelSlot();

        void showHelpSlot();
        void showInfoSlot();

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
