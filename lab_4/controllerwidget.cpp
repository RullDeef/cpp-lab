#include "controllerwidget.h"
#include "ui_controllerwidget.h"

ControllerWidget::ControllerWidget(Controller *controller)
    : QWidget(nullptr), ui(new Ui::Controller), controller(controller)
{
    ui->setupUi(this);

    ui->floorsLayout->addSpacerItem(new QSpacerItem(200, 0));
    for (int i = FLOORS_COUNT; i > 0; i--)
        addFloorButton(i);
    ui->floorsLayout->insertSpacerItem(0, new QSpacerItem(200, 0));

    connect(controller->getCabin(), &Cabin::stoppedSignal, this, &ControllerWidget::cabinVisited);
    floorBulbs[0]->setChecked(true);
}

ControllerWidget::~ControllerWidget()
{
    delete ui;
}

void ControllerWidget::cabinVisited(Cabin* cabin, int floor)
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
    floorBulbs.insert(floorBulbs.begin(), floorBulb);
    ui->floorsLayout->insertWidget(0, floorBulb);

    ControllerButton* button = new ControllerButton(floor);
    ControllerButtonWidget* buttonWidget = new ControllerButtonWidget(button);

    buttons.insert(buttons.begin(), button);
    buttonWidgets.insert(buttonWidgets.begin(), buttonWidget);

    ui->buttonsLayout->addWidget(buttonWidget);
    controller->addButton(button);
}
