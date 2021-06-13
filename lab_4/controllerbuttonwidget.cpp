#include "controllerbuttonwidget.h"

ControllerButtonWidget::ControllerButtonWidget(ControllerButton* button)
    : button(button)
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
    setText(QString::number(button->getFloorNumber()));

    connect(this, &QPushButton::pressed, this, &ControllerButtonWidget::buttonPressed);
    connect(button, &ControllerButton::releasedSignal, this, &ControllerButtonWidget::buttonReleased);
}

ControllerButton *ControllerButtonWidget::getControllerButton()
{
    return button;
}

void ControllerButtonWidget::buttonPressed()
{
    setDisabled(true);
    button->press();
}

void ControllerButtonWidget::buttonReleased(ControllerButton *button)
{
    setDisabled(false);
}
