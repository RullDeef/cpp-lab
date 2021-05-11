#pragma once

#include <memory>
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

    QGraphicsView* getGraphisView();

private:
    Ui::MainWindowClass ui;
    QGraphicsView* mainViewport;
};
