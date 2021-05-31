#include <QTimer>
#include <QDebug>
#include "cabin.h"

Cabin::Cabin(QObject *parent)
    : QObject(parent)
{
    door = new Door(this);
    setupConnections();
}

Cabin::Cabin(Door *door)
    : QObject(nullptr), door(door)
{
    setupConnections();
}

void Cabin::setTarget(int floor)
{
    targetFloor = floor;
    if (state == State::STOPPED && targetFloor != currFloor)
    {
        qDebug() << "target set! Floor: " << floor;
        door->close();
    }
}

void Cabin::startMoving()
{
    qDebug() << "start moving...";

    emit doorsClosing();
    QTimer::singleShot(floorTimeout, this, &Cabin::finishMoving);
}

void Cabin::finishMoving()
{
    direction = targetFloor < currFloor ? Direction::DOWN : Direction::UP;

    if (direction == Direction::UP)
        currFloor++;
    else if (direction == Direction::DOWN)
        currFloor--;

    if (currFloor == targetFloor)
    {
        qDebug() << "ding! arrived at floor: " << targetFloor;

        emit floorVisited(targetFloor, direction);

        emit doorsOpening();
        door->open();
    }
    else
    {
        emit floorSkipped(currFloor, direction);
        startMoving();
    }
}

void Cabin::doorsOpened()
{
    direction = Direction::NONE;
}

void Cabin::setupConnections()
{
    connect(door, &Door::opened, this, &Cabin::doorsOpened);
    connect(door, &Door::closed, this, &Cabin::startMoving);
}
