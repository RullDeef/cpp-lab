#include <QDebug>
#include "controller.h"


Controller::Controller(Cabin *cabin, Door *door)
    : cabin(cabin), door(door)
{
    connect(cabin, &Cabin::stoppedSignal, this, &Controller::cabinStoppedDispatcher);
    connect(door, &Door::closedSignal, this, &Controller::doorClosedDispatcher);
    connect(door, &Door::openedSignal, this, &Controller::doorOpenedDispatcher);
}

void Controller::addButton(ControllerButton *button)
{
    connect(button, &ControllerButton::pressedSignal, this, &Controller::buttonPressedDispatcher);
    connect(this, &Controller::releaseButton, [button](int floor)
    {
        if (floor == button->getFloorNumber())
            button->releaseButton();
    });
}

Cabin *Controller::getCabin()
{
    return cabin;
}

void Controller::cabinStoppedDispatcher(Cabin *cabin)
{
    int floor = cabin->getCurrFloor();

    if (floorRequested[floor - 1])
    {
        qDebug() << "cabin stopped at floor " << floor;
        floorRequested[floor - 1] = false;
        door->openDoor();
    }
    else
    {
        qDebug() << "cabin passed floor " << floor;
        cabin->move(currDirection);
    }
}

void Controller::buttonPressedDispatcher(ControllerButton *button)
{
    int floor = button->getFloorNumber();
    addTarget(floor);
}

void Controller::doorClosedDispatcher(Door *door)
{
    int currFloor = cabin->getCurrFloor();
    int targetFloor = getNextTargetFloor(currFloor, currDirection);

    if (targetFloor < currFloor)
        currDirection = Direction::DOWN;
    else
        currDirection = Direction::UP;

    cabin->move(currDirection);
}

void Controller::doorOpenedDispatcher(Door *door)
{
    int currFloor = cabin->getCurrFloor();
    floorRequested[currFloor - 1] = false;

    emit releaseButton(currFloor);

    if (hasRequests())
    {
        qDebug() << "start going to the next floor";
        int targetFloor = getNextTargetFloor(currFloor, currDirection);

        if (targetFloor < currFloor)
            currDirection = Direction::DOWN;
        else
            currDirection = Direction::UP;

        door->closeDoor();
    }
    else
    {
        qDebug() << "no more requested floors";
        state = State::FREE;
        currDirection = Direction::NONE;
    }
}

void Controller::addTarget(int floor)
{
    qDebug() << "requested floor: " << floor;

    if (state == State::FREE)
    {
        if (floor == cabin->getCurrFloor())
        {
            qDebug() << "requested floor is current floor. Do nothing";
            emit releaseButton(floor);
        }
        else
        {
            floorRequested[floor - 1] = true;
            state = State::BUSY;
            door->closeDoor();
        }
    }
    else
    {
        floorRequested[floor - 1] = true;
    }
}

bool Controller::hasRequests() const
{
    for (int i = 0; i < FLOORS_COUNT; i++)
        if (floorRequested[i])
            return true;

    return false;
}

int Controller::getNextTargetFloor(int currFloor, Direction dir) const
{
    if (dir == Direction::DOWN)
    {
        for (int i = currFloor - 1; i >= 0; i--)
            if (floorRequested[i])
                return i + 1;

        for (int i = currFloor - 1; i < FLOORS_COUNT; i++)
            if (floorRequested[i])
                return i + 1;
    }
    else
    {
        for (int i = currFloor - 1; i < FLOORS_COUNT; i++)
            if (floorRequested[i])
                return i + 1;

        for (int i = currFloor - 1; i >= 0; i--)
            if (floorRequested[i])
                return i + 1;
    }
    return 0;
}
