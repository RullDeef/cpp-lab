#ifndef CABIN_H
#define CABIN_H

#include <QObject>
#include <QTimer>
#include "common.h"


class Cabin : public QObject
{
    Q_OBJECT

public:
    enum class State
    {
        STOPPED,
        STARTED_MOVING,
        MOVING
    };

    Cabin();
    virtual ~Cabin() = default;

    int getCurrFloor() const;
    Direction getDirection() const;

signals:
    void movingSignal(Cabin* cabin, int floor);
    void startMovingSignal(Cabin* cabin, int floor);
    void stoppedSignal(Cabin* cabin, int floor);

public slots:
    void startMove(int targetFloor);
    void move();
    void stop();

private:
    int currFloor = 1;
    int targetFloor = 1;
    Direction direction = Direction::NONE;
    State state = State::STOPPED;
    QTimer timer;
};

#endif // CABIN_H
