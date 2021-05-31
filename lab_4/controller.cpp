#include <QDebug>
#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
}

void Controller::addTarget(int floor)
{
    qDebug() << "requested floor: " << floor;
    floorRequested[floor - 1] = true;

    if (state == State::FREE)
    {
        emit updateMainTarget(floor);
        state = State::BUSY;
    }
}

void Controller::floorReached(int floor, Direction dir)
{
    floorRequested[floor - 1] = false;
    emit floorVisited(floor);

    if (hasRequests())
    {
        qDebug() << "going to the next floor...";
        floor = getNextTargetFloor(floor, dir);
        emit updateMainTarget(floor);
    }
    else
    {
        qDebug() << "no more requests!";
        state = State::FREE;
    }
}

void Controller::floorPassed(int floor, Direction direction)
{
    qDebug() << "skipped floor " << floor;
    (void)direction;
    emit floorSkipped(floor);
}

bool Controller::hasRequests()
{
    for (int i = 0; i < FLOORS_COUNT; i++)
        if (floorRequested[i])
            return true;
    return false;
}

int Controller::getNextTargetFloor(int currFloor, Direction dir)
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
