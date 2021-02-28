#include <iostream>
#include <QtWidgets/QMessageBox>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QFileDialog>
#include <glm/gtc/matrix_transform.hpp>
#include "modelviewer.hpp"

ui::ModelViewer::ModelViewer(QWidget* parent)
    : QMainWindow(parent), updateLoopTimer(this), rotating(false), model_loaded(false)
{
    ui.setupUi(this);

    initPainter();
    initSignals();

    initTimer();
}

ui::ModelViewer::~ModelViewer()
{
    updateLoopTimer.stop();
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
    core::Model model;
    if (core::model_load(filename, model) == core::ErrorCode::success)
    {
        model_context = core::wrap_model(model, 0, 0, width(), height());
        model_loaded = true;
        return true;
    }
    
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

    if (model_loaded)
        paintModel();
}

void ui::ModelViewer::paintModel()
{
    if (painter.begin(this))
    {
        painter.setPen(pen);
        painter.setBrush(brush);

        // paint edges
        for (const auto& edge : model_context.model.edges)
        {
            core::Model::Vertex v1 = model_context.model.verts[edge.first];
            core::Model::Vertex v2 = model_context.model.verts[edge.second];

            glm::vec2 p1 = core::project(model_context, v1);
            glm::vec2 p2 = core::project(model_context, v2);

            painter.drawLine(QPointF(p1.x, p1.y), QPointF(p2.x, p2.y));
        }

        // paint verticies
        for (const auto& vertex : model_context.model.verts)
        {
            glm::vec2 point = core::project(model_context, vertex);
            painter.drawEllipse(QPointF(point.x, point.y), 2, 2);
        }

        painter.end();
    }
}

bool ui::ModelViewer::event(QEvent* event)
{
    if (event->type() == QEvent::Type::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        prev_mouse_pos = mouseEvent->localPos();

        if (mouseEvent->button() == Qt::MouseButton::RightButton)
            grabbing = true;
        else if (mouseEvent->button() == Qt::MouseButton::LeftButton)
            rotating = true;
    }
    else if (event->type() == QEvent::Type::MouseButtonRelease)
    {
        grabbing = false;
        rotating = false;
    }
    else if (event->type() == QEvent::Type::Wheel)
    {
        QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);
        double delta = wheelEvent->angleDelta().y() / 200.0;
        core::zoom(model_context, delta);
    }
    else if (event->type() == QEvent::Type::MouseMove)
    {
        if (grabbing)
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            QPointF curr_mouse_pos = mouseEvent->localPos();
            QPointF delta = curr_mouse_pos - prev_mouse_pos;
            prev_mouse_pos = curr_mouse_pos;

            constexpr auto sensetivity = 60.0f;
            delta /= sensetivity;

            core::grab(model_context, delta.x(), delta.y());

            repaint();
        }
        else if (rotating) // apply rotation to model_view
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            QPointF curr_mouse_pos = mouseEvent->localPos();
            QPointF delta = curr_mouse_pos - prev_mouse_pos;
            prev_mouse_pos = curr_mouse_pos;

            constexpr auto sensetivity = 60.0f;
            delta /= sensetivity;

            core::orbit_aroud_selection(model_context, delta.x(), delta.y());

            repaint();
        }
    }

    return QMainWindow::event(event);
}

void ui::ModelViewer::update()
{
    QWidget::update();
}
