#pragma once

#include <QtWidgets/QMainWindow>
#include <QPainter>
#include <QTimer>
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

        QPointF projectVertex(const core::Model::Vertex& vertex) const;

    private:
        void initMVP();
        void initPainter();
        void initTimer();

        void initSignals();

    public slots:
        void update();

        void loadModelSlot();

    private:
        Ui::ModelViewer ui;

        QTimer updateLoopTimer;

        core::Model model;

        glm::mat4 model_view;
        glm::mat4 view_zoom;
        glm::mat4 projection;

        bool rotating;
        QPointF start_rotation_pos;

        QPainter painter;
        QPen pen;
        QBrush brush;
    };
}
