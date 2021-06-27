#include <QDebug>
#include "cabin.h"

constexpr auto timeout = 1000;


Cabin::Cabin()
{
    timer.setSingleShot(false);
    connect(&timer, &QTimer::timeout, this, &Cabin::move);
    connect(this, &Cabin::startMovingSignal, this, &Cabin::move);
}

int Cabin::getCurrFloor() const
{
    return currFloor;
}

Direction Cabin::getDirection() const
{
    return direction;
}

void Cabin::startMove(int targetFloor)
{
    if (state == State::STOPPED)
    {
        state = State::STARTED_MOVING;
        qDebug() << "Cabin: started moving to floor " << targetFloor;
        this->targetFloor = targetFloor;
        emit startMovingSignal(this, currFloor);
    }
}

void Cabin::move()
{
    if (state == State::STARTED_MOVING)
    {
        timer.start(timeout);
        state = State::MOVING;
        return;
    }
    else if (state == State::MOVING)
    {
        qDebug() << "Cabin: at " << currFloor;
    }
    else
        return;

    state = State::MOVING;

    if (currFloor < targetFloor)
    {
        direction = Direction::UP;
        emit movingSignal(this, ++currFloor);
    }
    else if (targetFloor < currFloor)
    {
        direction = Direction::DOWN;
        emit movingSignal(this, --currFloor);
    }
    else
        emit movingSignal(this, currFloor);
}

void Cabin::stop()
{
    if (state == State::MOVING || state == State::STARTED_MOVING)
    {
        state = State::STOPPED;
        qDebug() << "stopped moving.";
        timer.stop();
        emit stoppedSignal(this, currFloor);
    }
}
