#pragma once

#include <QtWidgets/QMainWindow>
#include <QPainter>
#include <glm/glm.hpp>
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
        bool event(QEvent* event);

    private:
        Ui::ModelViewer ui;

        core::Model model;

        glm::mat4 projection;
        glm::mat4 view;

        bool rotating;
        QPointF start_rotation_pos;

        QPainter painter;
        QPen pen;
        QBrush brush;
    };
}
