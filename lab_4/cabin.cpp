#include <QTimer>
#include <QDebug>
#include "cabin.h"

constexpr int timeout = 1000;


int Cabin::getCurrFloor() const
{
    return currFloor;
}

void Cabin::move(Direction direction)
{
    qDebug() << "start moving...";
    this->direction = direction;
    state = State::MOVING;
    emit movingSignal(this);
    QTimer::singleShot(timeout, [this, direction]()
    {
        if (direction == Direction::UP)
            currFloor++;
        else if (direction == Direction::DOWN)
            currFloor--;

        state = State::STOPPED;
        emit stoppedSignal(this, currFloor);
    });
}
