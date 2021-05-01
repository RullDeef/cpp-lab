#include <iostream>
#include <QtWidgets/QMessageBox>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QFileDialog>
#include <glm/gtc/matrix_transform.hpp>
#include "modelviewer.hpp"

ui::ModelViewer::ModelViewer(QWidget* parent)
    : QMainWindow(parent), grabbing(false), rotating(false)
{
    ui.setupUi(this);

    pen.setColor(QColor::fromRgb(128, 256, 192));
    pen.setWidthF(2.0);

    connect(ui.modelLoadOpt, SIGNAL(triggered()), this, SLOT(loadModelSlot()));
    connect(ui.modelSaveOpt, SIGNAL(triggered()), this, SLOT(saveModelSlot()));
    connect(ui.helpOpt, SIGNAL(triggered()), this, SLOT(showHelpSlot()));
    connect(ui.infoOpt, SIGNAL(triggered()), this, SLOT(showInfoSlot()));

    core::ProjectedModel projection;
    core::Action action { core::ActionType::Init };
    action.viewport = core::alg::viewport_init(width(), height());
    handleErrorCode(core::model_viewer(projection, action));
}

ui::ModelViewer::~ModelViewer()
{
    core::ProjectedModel projection;
    core::Action action { core::ActionType::Destroy };
    handleErrorCode(core::model_viewer(projection, action));
}

void ui::ModelViewer::loadModelSlot()
{
    std::string filename;
    if (requestFilename(filename))
    {
        core::ProjectedModel projection;
        core::Action action = { core::ActionType::Load };
        action.filename = filename.c_str();
        handleErrorCode(core::model_viewer(projection, action));
    }
}

void ui::ModelViewer::saveModelSlot()
{
    std::string filename;
    if (requestFilename(filename))
    {
        core::ProjectedModel projection;
        core::Action action { core::ActionType::Save };
        action.filename = filename.c_str();
        handleErrorCode(core::model_viewer(projection, action));
    }
}

void ui::ModelViewer::showHelpSlot()
{
    QMessageBox::about(this, u8"Справка",
        u8"Перемещение модели параллельно плоскости экрана: Shift + ЛКМ\n"
        u8"Вращение модели: ЛКМ\n"
        u8"Масштабирование модели: СКМ"
    );
}

void ui::ModelViewer::showInfoSlot()
{
    QMessageBox::about(this, u8"О программе",
        u8"Лабораторная работа №1 по ООП.\n\n"
        u8"Выполнил: Клименко Алексей, ИУ7-45Б\n"
        u8"@ Март, 2021"
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
}

void ui::ModelViewer::paintEvent(QPaintEvent* event)
{
    QMainWindow::paintEvent(event);

    core::ProjectedModel projection;
    core::Action action = { core::ActionType::ComputeProjection };
    core::ErrorCode status = core::model_viewer(projection, action);

    if (status != core::ErrorCode::success)
        return;

    if (!painter.begin(this))
        return;

    painter.setPen(pen);
    paintProjection(projection);
    painter.end();
}

bool ui::ModelViewer::requestFilename(std::string& filename)
{
    QFileDialog dialog(this, u8"Выберите файл модели");

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
    const char* message = u8"Произошла неизвестная ошибка.";

    switch (status)
    {
    case core::ErrorCode::success:
        return true;

    case core::ErrorCode::invalid_viewport:
        message = u8"Некорректная область просмотра (veiwport)";
        break;

    case core::ErrorCode::bad_malloc:
        message = u8"Не удалось выделить достаточно памяти для работы.";
        break;

    case core::ErrorCode::invalid_file_name:
        message = u8"Указано некорректное имя файла.";
        break;

    case core::ErrorCode::cannot_open_file:
        message = u8"Не удалось открыть файл.";
        break;

    case core::ErrorCode::invalid_file:
        message = u8"Файл имеет некорректный формат.";
        break;

    case core::ErrorCode::unknown_action:
        message = u8"При взаимодействии с прикладным доменом, последний не смог распознать тип запрашиваемого действия.";
        break;
    }


    QMessageBox::critical(this, u8"Ошибка", message);
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
    action.dx = delta.x();
    action.dy = delta.y();

    if (grabbing)
        action.type = core::ActionType::Translate;
    else if (rotating)
        action.type = core::ActionType::Rotate;

    core::ProjectedModel projection;
    handleErrorCode(core::model_viewer(projection, action));
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
    core::ProjectedModel projection;
    core::Action action { core::ActionType::Scale };
    action.factor = event->angleDelta().y() / 180.0;
    handleErrorCode(core::model_viewer(projection, action));
    repaint();
}
