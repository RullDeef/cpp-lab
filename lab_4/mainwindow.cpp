#include <QLayout>
#include "controllerwidget.h"
#include "cabinwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
      // cabinWidget(new CabinWidget(new Cabin(new Door()))),
      // controllerWidget(new ControllerWidget(new Controller()))
{
    ui->setupUi(this);

    door = new Door();
    cabin = new Cabin();
    controller = new Controller(cabin, door);

    CabinWidget* cabinWidget = new CabinWidget(cabin, door);
    ui->centralwidget->layout()->addWidget(cabinWidget);

    ControllerWidget* controllerWidget = new ControllerWidget(controller);
    ui->centralwidget->layout()->addWidget(controllerWidget);

    // connect(ui->pushButton, &QPushButton::pressed, this, &MainWindow::pressButton);
    //
    // ControllerButton* buttons[5];
    //
    // for (size_t i = 0; i < sizeof(buttons) / sizeof(*buttons); i++)
    // {
    //     buttons[i] = new ControllerButton(i + 1);
    //     controller->addButton(buttons[i]);
    // }
    //
    // buttons[2]->pressButton();

    // ui->centralwidget->layout()->addWidget(cabinWidget);
    // ui->centralwidget->layout()->addWidget(controllerWidget);

    // elevator = new Elevator(&**controllerWidget, &**cabinWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete controller;
    //delete cabin;
    //delete door;
}
