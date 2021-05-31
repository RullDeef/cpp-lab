#include "controllerbutton.h"

ControllerButton::ControllerButton(QWidget *parent) :
    QPushButton(parent)
{
    setStyleSheet(
        "background-color: rgb(190, 160, 200);"
        "border-style: solid;"
        "border-width: 1px;"
        "border-radius: 16px;"
        "border-color: black;"
        "max-width:  32px;"
        "max-height: 32px;"
        "min-width:  32px;"
        "min-height: 32px;");

    auto f = font();
    f.setPointSize(16);
    setFont(f);

    setText("0");

    connect(this, &QPushButton::pressed, this, &ControllerButton::makeRequest);
}

ControllerButton::~ControllerButton()
{
}

void ControllerButton::makeRequest()
{
    emit requestFloor(floorNumber);
    setDisabled(true);
}

void ControllerButton::setNumber(int n)
{
    floorNumber = n;
    setText(QString::number(n));
}
