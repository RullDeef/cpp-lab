#ifndef CABIN_H
#define CABIN_H

#include <QObject>
#include "common.h"
#include "door.h"

class Cabin : public QObject
{
    Q_OBJECT

    enum class State
    {
        STOPPED,
        MOVING
    };

public:
    explicit Cabin(QObject *parent = nullptr);
    explicit Cabin(Door* door);

signals:
    void floorVisited(int floor, Direction direction);
    void floorSkipped(int floor, Direction direction = Direction::NONE);

    void doorsOpening();
    void doorsClosing();

public slots:
    void setTarget(int floor);

private slots:
    void startMoving();
    void finishMoving();
    void doorsOpened();

private:
    void setupConnections();

    Door* door;

    int currFloor = 1;
    int targetFloor = 0;
    State state = State::STOPPED;
    Direction direction = Direction::NONE;

    int floorTimeout = 2000;
};

#endif // CABIN_H
