#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cabinwidget.h"
#include "controllerwidget.h"
#include "elevator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Elevator* elevator;
    CabinWidget *cabinWidget;
    ControllerWidget *controllerWidget;
};
#endif // MAINWINDOW_H
