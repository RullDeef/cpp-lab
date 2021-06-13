#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
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
        WAITING_PASSENGERS,
        DETERMINE_NEXT_FLOOR,
        START_MOVING,
        CLOSING_DOORS,
        WAITING_FOR_ARRIVE,
        ARRIVED
    };

    Controller(Cabin* cabin, Door* door);
    virtual ~Controller() = default;

    void connectButton(ControllerButton* button);
    Cabin* getCabin();

signals:
    void releaseButton(int floor);

    void startMovingSignal(int targetFloor);

    void doorsOpeningSignal();
    void doorsClosingSignal();
    void cabinMoveSignal(int targetFloor);
    void cabinStopSignal();
    void cabinStoppedSignal();

public slots:
    void buttonPressedDispatcher(ControllerButton* button);
    void startMovingDispatcher(int targetFloor);

    void cabinMovingDispatcher(Cabin* cabin, int currFloor);
    void cabinStoppedDispatcher(Cabin* cabin);
    void moveCabin();
    void doorOpenedDispatcher(Door* door);

    void waitingTimeout();

private:
    bool hasRequests() const;

    int getNextTargetFloor() const;
    int getNextTargetFloor(int currFloor, Direction dir) const;

    State state = State::WAITING_PASSENGERS;
    bool floorRequested[FLOORS_COUNT] = { false };

    Cabin* cabin;
    Door* door;
    QTimer timer;
};

#endif // CONTROLLER_H
