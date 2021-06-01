#include "controllerbutton.h"


ControllerButton::ControllerButton(int floor)
    : floorNumber(floor)
{
}

ControllerButton::~ControllerButton()
{
}

int ControllerButton::getFloorNumber() const
{
    return floorNumber;
}

void ControllerButton::pressButton()
{
    state = State::PRESSED;
    emit pressedSignal(this);
}

void ControllerButton::releaseButton()
{
    state = State::RELEASED;
    emit releasedSignal(this);
}
