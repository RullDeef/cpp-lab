#include <iostream>
#include <QtWidgets/QMessageBox>
#include <QPainter>
#include "modelviewer.hpp"

constexpr auto default_scale = 40.0;

ui::ModelViewer::ModelViewer(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initial_transform = QTransform(
        default_scale, 0, 0, -default_scale, 320, 240
    );

    pen.setColor(QColor::fromRgb(128, 256, 192));
    pen.setWidthF(2 / default_scale);

    brush.setColor(QColor::fromRgb(200, 200, 200));

    preloadModel("model.txt");
}

ui::ModelViewer::~ModelViewer()
{
}

bool ui::ModelViewer::preloadModel(const char* filename)
{
    if (core::load_model(filename, active_model) == core::ErrorCode::success)
        return true;
    
    QMessageBox messageBox;
    messageBox.setText(tr(u8"Не удалось загрузить модель из файла."));
    messageBox.exec();
    return false;
}

void ui::ModelViewer::paintEvent(QPaintEvent* event)
{
    QMainWindow::paintEvent(event);
    paintModel(active_model);
}

void ui::ModelViewer::paintModel(const core::Model& model)
{
    if (painter.begin(this))
    {
        painter.setPen(pen);
        painter.setBrush(brush);
        painter.setTransform(initial_transform);

        // paint edges
        for (const auto& edge : model.edges)
        {
            core::Model::Vertex v1 = model.verts[edge.first];
            core::Model::Vertex v2 = model.verts[edge.second];

            painter.drawLine(v1.x, v1.y, v2.x, v2.y);
        }

        // paint verticies
        for (const auto& vertex : model.verts)
            painter.drawEllipse(QPointF(vertex.x, vertex.y), 2 / default_scale, 2 / default_scale);

        painter.resetTransform();
        painter.end();
    }
}
