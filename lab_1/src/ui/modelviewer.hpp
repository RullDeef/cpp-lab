#pragma once

#include <QtWidgets/QMainWindow>
#include <QPainter>
#include "ui_modelviewer.h"
#include "core/model.hpp"

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

        void paintModel(const core::Model& model);

    private:
        Ui::ModelViewer ui;

        core::Model active_model;
        QTransform initial_transform;

        QPainter painter;
        QPen pen;
        QBrush brush;
    };
}
