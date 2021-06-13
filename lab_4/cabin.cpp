#include <QDebug>
#include "cabin.h"


Cabin::Cabin()
{
    timer.setSingleShot(false);
    connect(&timer, &QTimer::timeout, this, &Cabin::move);
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
        timer.start(1000);
    }
}

void Cabin::move()
{
    if (state == State::STARTED_MOVING || state == State::MOVING)
    {
        state = State::MOVING;
        qDebug() << "Cabin: at " << currFloor;

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
}

void Cabin::stop()
{
    state = State::STOPPED;
    qDebug() << "stopped moving.";
    timer.stop();
    emit stoppedSignal(this, currFloor);
}
