#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>

#include "controller.h"
#include "cabin.h"

class Elevator : public QObject
{
    Q_OBJECT

public:
    Elevator(Controller* controller, Cabin* cabin);
    ~Elevator();

private:
    Controller* controller;
    Cabin* cabin;
};

#endif // ELEVATOR_H
