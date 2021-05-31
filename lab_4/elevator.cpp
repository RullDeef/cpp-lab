#include "elevator.h"

Elevator::Elevator(Controller *controller, Cabin *cabin)
    : controller(controller), cabin(cabin)
{
    connect(cabin, &Cabin::floorVisited, controller, &Controller::floorReached);
    connect(cabin, &Cabin::floorSkipped, controller, &Controller::floorPassed);
    connect(controller, &Controller::updateMainTarget, cabin, &Cabin::setTarget);
}

Elevator::~Elevator()
{
    delete cabin;
    delete controller;
}
