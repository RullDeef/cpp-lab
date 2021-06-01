#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "common.h"
#include "cabin.h"
#include "door.h"
#include "controllerbutton.h"


class Controller : public QObject
{
    Q_OBJECT

public:
    enum class State
    {
        FREE,
        BUSY
    };

    explicit Controller(Cabin* cabin, Door* door);

    void addButton(ControllerButton* button);
    Cabin* getCabin();

signals:
    void releaseButton(int floor);

public slots:
    void cabinStoppedDispatcher(Cabin* cabin);
    void buttonPressedDispatcher(ControllerButton* button);
    void doorClosedDispatcher(Door* door);
    void doorOpenedDispatcher(Door* door);

private:
    void addTarget(int floor);

    bool hasRequests() const;
    int getNextTargetFloor(int currFloor, Direction dir) const;

    State state = State::FREE;
    Direction currDirection = Direction::NONE;
    bool floorRequested[FLOORS_COUNT] = { false };

    Cabin* cabin;
    Door* door;
};

#endif // CONTROLLER_H
