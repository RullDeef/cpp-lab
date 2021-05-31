#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "common.h"

class Controller : public QObject
{
    Q_OBJECT

    enum class State
    {
        FREE,
        BUSY
    };

public:
    explicit Controller(QObject *parent = nullptr);

signals:
    void floorVisited(int floor);
    void floorSkipped(int floor);
    void updateMainTarget(int floor);

public slots:
    void addTarget(int floor);
    void floorReached(int floor, Direction dir);
    void floorPassed(int floor, Direction direction);

private:
    bool hasRequests();
    int getNextTargetFloor(int currFloor, Direction dir);

    bool floorRequested[FLOORS_COUNT] = { false };

    State state = State::FREE;
};

#endif // CONTROLLER_H
