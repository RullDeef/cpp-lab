#include <iostream>
#include <QtWidgets/QMessageBox>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QFileDialog>
#include <glm/gtc/matrix_transform.hpp>
#include "modelviewer.hpp"

ui::ModelViewer::ModelViewer(QWidget* parent)
    : QMainWindow(parent), updateLoopTimer(this), rotating(false)
{
    ui.setupUi(this);

    initMVP();
    initPainter();
    initSignals();

    initTimer();
}

ui::ModelViewer::~ModelViewer()
{
    updateLoopTimer.stop();
}

void ui::ModelViewer::initMVP()
{
    double ratio = static_cast<double>(width()) / height();

    projection = glm::perspective(glm::radians(75.0), ratio, 0.1, 1000.0);
    model_view = glm::identity<glm::mat4>();
    
    view_zoom = glm::rotate(glm::identity<glm::mat4>(), (float)glm::radians(180.0), glm::vec3(1, 0, 0));
    view_zoom = glm::translate(view_zoom, glm::vec3(0.0, 0.0, -10.0));
}

void ui::ModelViewer::initPainter()
{
    pen.setColor(QColor::fromRgb(128, 256, 192));
    pen.setWidthF(2.0);

    brush.setColor(QColor::fromRgb(225, 20, 20));
}

void ui::ModelViewer::initTimer()
{
    connect(&updateLoopTimer, SIGNAL(timeout()), this, SLOT(update()));
    updateLoopTimer.start(1000 / 60);
}

void ui::ModelViewer::initSignals()
{
    connect(ui.modelLoadOpt, SIGNAL(triggered()), this, SLOT(loadModelSlot()));
}

bool ui::ModelViewer::preloadModel(const char* filename)
{
    if (core::load_model(filename, model) == core::ErrorCode::success)
        return true;
    
    QMessageBox messageBox;
    messageBox.setText(u8"Не удалось загрузить модель из файла.");
    messageBox.exec();
    return false;
}

void ui::ModelViewer::loadModelSlot()
{
    QFileDialog dialog(this, u8"Выберите файл модели");

    if (dialog.exec())
    {
        QStringList filenames = dialog.selectedFiles();
        if (filenames.count() == 1)
            preloadModel(filenames[0].toStdString().c_str());
    }
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

            painter.drawLine(projectVertex(v1), projectVertex(v2));
        }

        // paint verticies
        for (const auto& vertex : model.verts)
            painter.drawEllipse(projectVertex(vertex), 2, 2);

        painter.end();
    }
}

bool ui::ModelViewer::event(QEvent* event)
{
    if (event->type() == QEvent::Type::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::MouseButton::LeftButton)
        {
            rotating = true;
            start_rotation_pos = mouseEvent->localPos();
        }
    }
    else if (event->type() == QEvent::Type::MouseButtonRelease)
    {
        if (static_cast<QMouseEvent*>(event)->button() == Qt::MouseButton::LeftButton)
            rotating = false;
    }
    else if (event->type() == QEvent::Type::Wheel)
    {
        QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);

        int delta = wheelEvent->angleDelta().y();
        double scale = 1 + delta / 10.0;

        ///// model_view *= QTransform(scale, 0, 0, scale, 0, 0);
    }
    else if (event->type() == QEvent::Type::MouseMove)
    {
        if (rotating) // apply rotation to model_view
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            QPointF curr_rotation_pos = mouseEvent->localPos();
            QPointF delta = curr_rotation_pos - start_rotation_pos;
            start_rotation_pos = curr_rotation_pos;

            constexpr auto sensetivity = 20.0f;

            model_view = glm::rotate(glm::identity<glm::mat4>(), -(float)delta.x() / sensetivity, glm::vec3(0.0, 1.0, 0.0))
                * glm::rotate(glm::identity<glm::mat4>(), (float)delta.y() / sensetivity, glm::vec3(1.0, 0.0, 0.0)) * model_view;

            repaint();
        }
    }

    return QMainWindow::event(event);
}

void ui::ModelViewer::update()
{
    QWidget::update();
}

QPointF ui::ModelViewer::projectVertex(const core::Model::Vertex& vertex) const
{
    glm::vec3 result = glm::project(glm::vec3(vertex.x, vertex.y, vertex.z),
        view_zoom * model_view,
        projection,
        glm::uvec4(0, 0, width(), height()));
    
    return QPointF(result.x, (float)height() - (float)result.y);
}
