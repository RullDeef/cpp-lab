#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    mainViewport = ui.mainViewport;
}

QGraphicsView* MainWindow::getGraphisView()
{
    return mainViewport;
}
