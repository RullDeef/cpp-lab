#include <iostream>
#include <QtWidgets/QMessageBox>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QFileDialog>
#include <glm/gtc/matrix_transform.hpp>
#include "modelviewer.hpp"

ui::ModelViewer::ModelViewer(QWidget* parent)
    : QMainWindow(parent), updateLoopTimer(this),
    model_loaded(false), grabbing(false), rotating(false)
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

    selected_pen.setColor(QColor::fromRgb(225, 180, 64));
    selected_pen.setWidthF(3.0);
}

void ui::ModelViewer::initTimer()
{
    connect(&updateLoopTimer, SIGNAL(timeout()), this, SLOT(update()));
    updateLoopTimer.start(1000 / 60);
}

void ui::ModelViewer::initSignals()
{
    connect(ui.modelLoadOpt, SIGNAL(triggered()), this, SLOT(loadModelSlot()));
    connect(ui.modelNewOpt, SIGNAL(triggered()), this, SLOT(newModelSlot()));
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

void ui::ModelViewer::newModelSlot()
{
    model_context = core::wrap_model(core::default_cube(2.0), 0, 0, width(), height());
    model_loaded = true;
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

        painter.setPen(selected_pen);

        // paint selected verticies
        for (unsigned int i : model_context.selected_verts)
        {
            core::Model::Vertex v = model_context.model.verts[i];
            glm::vec2 p = core::project(model_context, v);
            painter.drawEllipse(QPointF(p.x, p.y), 2, 2);
        }

        painter.end();
    }
}

void ui::ModelViewer::mouseMoveEvent(QMouseEvent* event)
{
    QPointF curr_mouse_pos = event->localPos();
    QPointF delta = curr_mouse_pos - prev_mouse_pos;
    prev_mouse_pos = curr_mouse_pos;

    constexpr auto grab_sensetivity = 60.0f;
    constexpr auto rotate_sensetivity = 60.0f;

    if (grabbing)
    {
        delta /= grab_sensetivity;
        core::grab(model_context, delta.x(), delta.y());
    }
    else if (rotating)
    {
        delta /= rotate_sensetivity;
        core::orbit_around_selection(model_context, delta.x(), delta.y());
    }
}

void ui::ModelViewer::mousePressEvent(QMouseEvent* event)
{
    prev_mouse_pos = event->localPos();

    if (event->button() == Qt::MouseButton::MiddleButton)
    {
        if (QApplication::queryKeyboardModifiers().testFlag(Qt::KeyboardModifier::ShiftModifier))
            grabbing = true;
        else
            rotating = true;
    }
}

void ui::ModelViewer::mouseReleaseEvent(QMouseEvent* event)
{
    grabbing = false;
    rotating = false;

    if (event->button() == Qt::MouseButton::LeftButton)
    {
        if (QApplication::queryKeyboardModifiers().testFlag(Qt::KeyboardModifier::ShiftModifier))
            core::toggle_selection(model_context, event->localPos().x(), event->localPos().y());
        else
            core::select(model_context, event->localPos().x(), event->localPos().y());
    }
    else if (event->button() == Qt::MouseButton::RightButton)
    {
        core::add_vertex(model_context, event->localPos().x(), event->localPos().y());
    }
}

void ui::ModelViewer::wheelEvent(QWheelEvent* event)
{
    QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);
    double delta = wheelEvent->angleDelta().y() / 200.0;
    core::zoom(model_context, delta);
}

void ui::ModelViewer::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key::Key_E)
    {
        core::connect_selected_verts(model_context);
    }
    else if (event->key() == Qt::Key::Key_Delete)
    {
        core::remove_selected(model_context);
    }
}

void ui::ModelViewer::update()
{
    QWidget::update();
}
