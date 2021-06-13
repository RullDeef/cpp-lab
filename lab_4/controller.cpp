#include <QDebug>
#include "controller.h"


Controller::Controller(Cabin *cabin, Door *door)
    : cabin(cabin), door(door)
{
    connect(cabin, &Cabin::movingSignal, this, &Controller::moveCabin);
    connect(cabin, &Cabin::stoppedSignal, this, &Controller::cabinStoppedDispatcher);
    connect(door, &Door::closedSignal, this, &Controller::moveCabin);
    connect(door, &Door::openedSignal, this, &Controller::doorOpenedDispatcher);

    connect(this, &Controller::startMovingSignal, door, &Door::opening);
    connect(this, &Controller::cabinMoveSignal, cabin, &Cabin::startMove);
    connect(this, &Controller::cabinStopSignal, cabin, &Cabin::stop);

    connect(this, &Controller::doorsOpeningSignal, door, &Door::opening);
    connect(this, &Controller::doorsClosingSignal, door, &Door::closing);

    // добавить нормальный жц для контроллера.
}

void Controller::connectButton(ControllerButton *button)
{
    connect(button, &ControllerButton::pressedSignal, this, &Controller::buttonPressedDispatcher);
    connect(this, &Controller::releaseButton, [button](int floor)
    {
        if (floor == button->getFloorNumber())
            button->release();
    });
}

Cabin *Controller::getCabin()
{
    return cabin;
}

void Controller::buttonPressedDispatcher(ControllerButton *button)
{
    bool started = hasRequests();
    state = State::DETERMINE_NEXT_FLOOR;
    int floor = button->getFloorNumber();

    floorRequested[floor - 1] = true;
    if (!started || floor == cabin->getCurrFloor())
        emit startMovingSignal(getNextTargetFloor());
}

void Controller::startMovingDispatcher(int targetFloor)
{
    if (state == State::DETERMINE_NEXT_FLOOR)
    {
        state = State::START_MOVING;
        emit doorsOpeningSignal();
    }
    else
        qDebug() << "Controller: ignored transition";
}

void Controller::cabinMovingDispatcher(Cabin *cabin, int currFloor)
{
    state = State::WAITING_FOR_ARRIVE;
    if (floorRequested[currFloor - 1])
        emit cabinStopSignal();
    else
    {
        if (getNextTargetFloor() != 0)
            emit cabinMoveSignal(getNextTargetFloor());
    }
}

void Controller::cabinStoppedDispatcher(Cabin *cabin)
{
    if (state == State::WAITING_FOR_ARRIVE)
    {
        state = State::ARRIVED;
        qDebug() << "cabin stopped at floor " << cabin->getCurrFloor();
        emit doorsOpeningSignal();
    }
    else
        qDebug() << "Controller: ignored transition to CABIN_STOPPED";
}

void Controller::moveCabin()
{
    state = State::WAITING_FOR_ARRIVE;
    if (floorRequested[cabin->getCurrFloor() - 1])
        emit cabinStopSignal();
    else if (getNextTargetFloor() != 0)
        emit cabinMoveSignal(getNextTargetFloor());
}

void Controller::doorOpenedDispatcher(Door *door)
{
    state = State::WAITING_PASSENGERS;
    qDebug() << "waiting passengers...";

    int currFloor = cabin->getCurrFloor();
    floorRequested[currFloor - 1] = false;

    emit releaseButton(currFloor);
    //emit doorsClosingSignal();

    timer.disconnect();
    connect(&timer, &QTimer::timeout, this, &Controller::waitingTimeout);
    timer.start(2000);
}

void Controller::waitingTimeout()
{
    state = State::CLOSING_DOORS;
    qDebug() << "end waiting";
    timer.stop();
    emit doorsClosingSignal();
}

bool Controller::hasRequests() const
{
    for (int i = 0; i < FLOORS_COUNT; i++)
        if (floorRequested[i])
            return true;

    return false;
}

int Controller::getNextTargetFloor() const
{
    int currFloor = cabin->getCurrFloor();
    Direction dir = cabin->getDirection();

    return getNextTargetFloor(currFloor, dir);
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
