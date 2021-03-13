#include <iostream>
#include <QtWidgets/QMessageBox>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QFileDialog>
#include <glm/gtc/matrix_transform.hpp>
#include "modelviewer.hpp"

ui::ModelViewer::ModelViewer(QWidget* parent)
    : QMainWindow(parent), model_loaded(false), grabbing(false), rotating(false)
{
    ui.setupUi(this);

    pen.setColor(QColor::fromRgb(128, 256, 192));
    pen.setWidthF(2.0);

    connect(ui.modelLoadOpt, SIGNAL(triggered()), this, SLOT(loadModelSlot()));
    connect(ui.modelSaveOpt, SIGNAL(triggered()), this, SLOT(saveModelSlot()));
    connect(ui.helpOpt, SIGNAL(triggered()), this, SLOT(showHelpSlot()));
    connect(ui.infoOpt, SIGNAL(triggered()), this, SLOT(showInfoSlot()));

    core::Action action { core::ActionType::Init };
    action.viewport = { 0, 0, width(), height() };
    handleErrorCode(core::model_viewer(context, action));
}

ui::ModelViewer::~ModelViewer()
{
    core::Action action { core::ActionType::Destroy };
    handleErrorCode(core::model_viewer(context, action));
}

void ui::ModelViewer::loadModelSlot()
{
    std::string filename;
    if (requestFilename(filename))
    {
        core::Action action = { core::ActionType::Load };
        action.filename = filename.c_str();
        if (handleErrorCode(core::model_viewer(context, action)))
            model_loaded = true;
    }
}

void ui::ModelViewer::saveModelSlot()
{
    std::string filename;
    if (requestFilename(filename))
    {
        core::Action action { core::ActionType::Save };
        action.filename = filename.c_str();
        handleErrorCode(core::model_viewer(context, action));
    }
}

void ui::ModelViewer::showHelpSlot()
{
    QMessageBox::about(this, u8"�������",
        u8"����������� ������ ����������� ��������� ������: Shift + ���\n"
        u8"�������� ������: ���\n"
        u8"��������������� ������: ���"
    );
}

void ui::ModelViewer::showInfoSlot()
{
    QMessageBox::about(this, u8"� ���������",
        u8"������������ ������ �1 �� ���.\n\n"
        u8"��������: �������� �������, ��7-45�\n"
        u8"@ ����, 2021"
    );
}

void ui::ModelViewer::paintProjection(const core::ProjectedModel& prj)
{
    // paint edges
    for (unsigned int i = 0; i < prj.edges_count; i++)
    {
        core::screen_point p1 = prj.edges[i].p1;
        core::screen_point p2 = prj.edges[i].p2;

        painter.drawLine(QPoint(p1.x, p1.y), QPoint(p2.x, p2.y));
    }

    // paint verticies
    for (unsigned int i = 0; i < prj.verts_count; i++)
    {
        core::screen_point p = prj.verts[i];

        painter.drawEllipse(QPoint(p.x, p.y), 2, 2);
    }
}

void ui::ModelViewer::paintEvent(QPaintEvent* event)
{
    QMainWindow::paintEvent(event);

    if (!model_loaded)
        return;

    if (!painter.begin(this))
        return;

    painter.setPen(pen);
    paintProjection(context.projection);
    painter.end();
}

bool ui::ModelViewer::requestFilename(std::string& filename)
{
    QFileDialog dialog(this, u8"�������� ���� ������");

    if (!dialog.exec())
        return false;

    QStringList filenames = dialog.selectedFiles();
    if (filenames.count() != 1)
        return false;

    filename = filenames[0].toStdString();
    return true;
}

// true = good
bool ui::ModelViewer::handleErrorCode(core::ErrorCode status)
{
    const char* message = u8"��������� ����������� ������.";

    switch (status)
    {
    case core::ErrorCode::success:
        return true;

    case core::ErrorCode::invalid_viewport:
        message = u8"������������ ������� ��������� (veiwport)";
        break;

    case core::ErrorCode::bad_malloc:
        message = u8"�� ������� �������� ���������� ������ ��� ������.";
        break;

    case core::ErrorCode::invalid_file_name:
        message = u8"������� ������������ ��� �����.";
        break;

    case core::ErrorCode::cannot_open_file:
        message = u8"�� ������� ������� ����.";
        break;

    case core::ErrorCode::invalid_file:
        message = u8"���� ����� ������������ ������.";
        break;

    case core::ErrorCode::unknown_action:
        message = u8"��� �������������� � ���������� �������, ��������� �� ���� ���������� ��� �������������� ��������.";
        break;
    }


    QMessageBox::critical(this, u8"������", message);
    return false;
}

void ui::ModelViewer::mouseMoveEvent(QMouseEvent* event)
{
    if (!grabbing && !rotating)
        return;

    QPointF curr_mouse_pos = event->localPos();
    QPointF delta = curr_mouse_pos - prev_mouse_pos;
    prev_mouse_pos = curr_mouse_pos;

    core::Action action {};
    if (grabbing)
    {
        action.type = core::ActionType::Translate;
        action.translate = { delta.x(), delta.y() };
    }
    else if (rotating)
    {
        action.type = core::ActionType::Rotate;
        action.rotate = { delta.x(), delta.y() };
    }

    handleErrorCode(core::model_viewer(context, action));
    repaint();
}

void ui::ModelViewer::mousePressEvent(QMouseEvent* event)
{
    prev_mouse_pos = event->localPos();

    if (event->button() == Qt::MouseButton::LeftButton)
    {
        if (QApplication::queryKeyboardModifiers().testFlag
                (Qt::KeyboardModifier::ShiftModifier))
            grabbing = true;
        else
            rotating = true;
    }
}

void ui::ModelViewer::mouseReleaseEvent(QMouseEvent* event)
{
    grabbing = false;
    rotating = false;
}

void ui::ModelViewer::wheelEvent(QWheelEvent* event)
{
    core::Action action { core::ActionType::Scale };
    action.scale.factor = event->angleDelta().y() / 180.0;
    handleErrorCode(core::model_viewer(context, action));
    repaint();
}
