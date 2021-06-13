#include <QDebug>
#include "controllerbutton.h"


ControllerButton::ControllerButton(int floor)
    : floorNumber(floor)
{
}

int ControllerButton::getFloorNumber() const
{
    return floorNumber;
}

void ControllerButton::press()
{
    if (state == State::RELEASED)
    {
        state = State::PRESSED;
        emit pressedSignal(this);
    }
}

void ControllerButton::release()
{
    if (state == State::PRESSED)
    {
        state = State::RELEASED;
        emit releasedSignal(this);
    }
}
