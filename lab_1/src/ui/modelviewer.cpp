#include <iostream>
#include <QtWidgets/QMessageBox>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <glm/gtc/matrix_transform.hpp>
#include "modelviewer.hpp"

// constexpr auto default_scale = 40.0;

ui::ModelViewer::ModelViewer(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    double ratio = static_cast<double>(width()) / height();
    // double scale_factor = glm::min(width(), height()) / 2.0;

    projection = glm::perspective(glm::radians(75.0), ratio, 0.1, 1000.0);
    // view = glm::identity<glm::mat4>();
    // view = glm::translate(view, glm::vec3(0.0, 0.0, -10.0));
    rotating = false;

    pen.setColor(QColor::fromRgb(128, 256, 192));
    pen.setWidthF(2.0);

    brush.setColor(QColor::fromRgb(200, 200, 200));

    preloadModel("model.txt");
}

ui::ModelViewer::~ModelViewer()
{
}

bool ui::ModelViewer::preloadModel(const char* filename)
{
    if (core::load_model(filename, model) == core::ErrorCode::success)
        return true;
    
    QMessageBox messageBox;
    messageBox.setText(tr(u8"Не удалось загрузить модель из файла."));
    messageBox.exec();
    return false;
}

void ui::ModelViewer::paintEvent(QPaintEvent* event)
{
    QMainWindow::paintEvent(event);
    paintModel(model);
}

void ui::ModelViewer::paintModel(const core::Model& model)
{
    if (painter.begin(this))
    {
        painter.setPen(pen);
        painter.setBrush(brush);

        // paint edges
        for (const auto& edge : model.edges)
        {
            core::Model::Vertex v1 = model.verts[edge.first];
            core::Model::Vertex v2 = model.verts[edge.second];

            glm::vec3 gv1 = glm::project(glm::vec3(v1.x, v1.y, v1.z),
                glm::identity<glm::mat4>(),
                projection,
                glm::uvec4(0, 0, width(), height()));

            glm::vec3 gv2 = glm::project(glm::vec3(v2.x, v2.y, v2.z),
                glm::identity<glm::mat4>(),
                projection,
                glm::uvec4(0, 0, width(), height()));

            painter.drawLine(QPointF(gv1.x, gv1.y), QPointF(gv2.x, gv2.y));
        }

        // paint verticies
        for (const auto& vertex : model.verts)
        {
            glm::vec3 gv = glm::project(glm::vec3(vertex.x, vertex.y, vertex.z),
                glm::identity<glm::mat4>(),
                projection,
                glm::uvec4(0, 0, width(), height()));

            painter.drawEllipse(QPointF(gv.x, gv.y), 2, 2);
        }

        painter.end();
    }
}

bool ui::ModelViewer::event(QEvent* event)
{
    if (event->type() == QEvent::Type::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::MouseButton::MiddleButton)
        {
            rotating = true;
            start_rotation_pos = mouseEvent->localPos();
        }
    }
    else if (event->type() == QEvent::Type::MouseButtonRelease)
    {
        if (static_cast<QMouseEvent*>(event)->button() == Qt::MouseButton::MiddleButton)
            rotating = false;
    }
    else if (event->type() == QEvent::Type::Wheel)
    {
        QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);

        int delta = wheelEvent->angleDelta().y();
        double scale = 1 + delta / 10.0;

        ///// view *= QTransform(scale, 0, 0, scale, 0, 0);
    }
    else if (event->type() == QEvent::Type::MouseMove)
    {
        if (rotating) // apply translation to view
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            QPointF curr_rotation_pos = mouseEvent->localPos();
            QPointF delta = curr_rotation_pos - start_rotation_pos;
            
            // view *= QTransform(1, 0, 0, 1, delta.x(), delta.y());
            start_rotation_pos = curr_rotation_pos;

            repaint();
        }
    }

    return QMainWindow::event(event);
}
