#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>

#include "controller.h"
#include "cabin.h"
#include "controllerbutton.h"


class Elevator : public QObject
{
    Q_OBJECT

public:
    Elevator(Controller* controller, Cabin* cabin);
    ~Elevator();

    void addButton(ControllerButton* button);

protected slots:
    void buttonPressed(ControllerButton* button);

private:
    Controller* controller;
    Cabin* cabin;
};

#endif // ELEVATOR_H
