#include "controllerwidget.h"
#include "ui_controllerwidget.h"

ControllerWidget::ControllerWidget(Controller *controller)
    : QWidget(nullptr), ui(new Ui::Controller), controller(controller)
{
    ui->setupUi(this);

    ui->floorsLayout->addSpacerItem(new QSpacerItem(200, 0));
    for (int i = 1; i <= FLOORS_COUNT; i++)
        addFloorButton(i);
    ui->floorsLayout->addSpacerItem(new QSpacerItem(200, 0));

    floorVisited(1);
    connect(controller, &Controller::floorVisited, this, &ControllerWidget::floorVisited);
    connect(controller, &Controller::floorSkipped, this, &ControllerWidget::floorSkipped);
}

ControllerWidget::~ControllerWidget()
{
    delete ui;
}

Controller *ControllerWidget::operator->()
{
    return controller;
}

Controller &ControllerWidget::operator*()
{
    return *controller;
}

void ControllerWidget::requestFloor(int floor)
{
    controllerButtons[floor - 1]->setDisabled(true);
    controller->addTarget(floor);
}

void ControllerWidget::floorVisited(int floor)
{
    controllerButtons[floor - 1]->setDisabled(false);

    for (auto& bulb : floorBulbs)
        bulb->setChecked(false);
    floorBulbs[floor - 1]->setChecked(true);
}

void ControllerWidget::floorSkipped(int floor)
{
    for (auto& bulb : floorBulbs)
        bulb->setChecked(false);
    floorBulbs[floor - 1]->setChecked(true);
}

void ControllerWidget::addFloorButton(int floor)
{
    QRadioButton *floorBulb = new QRadioButton();
    floorBulb->setText(QString::number(floor));
    floorBulb->setDisabled(true);
    floorBulbs.push_back(floorBulb);

    ui->floorsLayout->addWidget(floorBulb);

    ControllerButton *button = new ControllerButton();
    button->setNumber(floor);
    controllerButtons.push_back(button);
    ui->buttonsLayout->addWidget(button);
    connect(button, &ControllerButton::requestFloor, this, &ControllerWidget::requestFloor);
}
