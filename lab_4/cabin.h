#ifndef CABIN_H
#define CABIN_H

#include <QObject>
#include "common.h"
#include "door.h"


class Cabin : public QObject
{
    Q_OBJECT

public:
    enum class State
    {
        STOPPED,
        MOVING
    };

    Cabin() = default;

    int getCurrFloor() const;

signals:
    void movingSignal(Cabin* cabin);
    void stoppedSignal(Cabin* cabin, int floor);

public slots:
    void move(Direction direction);

private:
    int currFloor = 1;
    State state = State::STOPPED;
    Direction direction = Direction::NONE;
};

#endif // CABIN_H
