#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      cabinWidget(new CabinWidget(new Cabin(new Door()))),
      controllerWidget(new ControllerWidget(new Controller()))
{
    ui->setupUi(this);
    ui->centralwidget->layout()->addWidget(cabinWidget);
    ui->centralwidget->layout()->addWidget(controllerWidget);

    elevator = new Elevator(&**controllerWidget, &**cabinWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete elevator;
}
