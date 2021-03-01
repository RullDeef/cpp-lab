#pragma once

#include <QtWidgets/QMainWindow>
#include <QPainter>
#include <QTimer>
#include "ui_modelviewer.h"
#include "core/modelcontext.hpp"

namespace ui
{
    class ModelViewer : public QMainWindow
    {
        Q_OBJECT

    public:
        ModelViewer(QWidget *parent = Q_NULLPTR);
        ~ModelViewer();

    protected:
        bool preloadModel(const char *filename);
        void paintEvent(QPaintEvent* event);

        void mouseMoveEvent(QMouseEvent* event);
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void wheelEvent(QWheelEvent* event);
        void keyPressEvent(QKeyEvent* event);

        void paintModel();

    private:
        void initPainter();
        void initTimer();
        void initSignals();

    public slots:
        void update();
        void loadModelSlot();

        void newModelSlot();

    private:
        Ui::ModelViewer ui;

        QTimer updateLoopTimer;

        bool model_loaded;
        core::ModelContext model_context;

        bool grabbing;
        bool rotating;
        QPointF prev_mouse_pos;

        QPainter painter;

        // regular pen
        QPen pen;
        QBrush brush;

        // selected pen
        QPen selected_pen;
    };
}
