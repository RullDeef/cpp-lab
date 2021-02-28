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

        void paintModel();
        bool event(QEvent* event);

    private:
        void initPainter();
        void initTimer();
        void initSignals();

    public slots:
        void update();
        void loadModelSlot();

    private:
        Ui::ModelViewer ui;

        QTimer updateLoopTimer;

        bool model_loaded;
        core::ModelContext model_context;

        bool grabbing;
        bool rotating;
        QPointF prev_mouse_pos;

        QPainter painter;
        QPen pen;
        QBrush brush;
    };
}
