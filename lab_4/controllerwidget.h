#ifndef CONTROLLERWIDGET_H
#define CONTROLLERWIDGET_H

#include <QWidget>
#include <QRadioButton>
#include "common.h"
#include "controller.h"
#include "controllerbutton.h"

namespace Ui {
class Controller;
}

class ControllerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControllerWidget(Controller* controller);
    ~ControllerWidget();

    Controller* operator->();
    Controller& operator*();

public slots:
    void requestFloor(int floor);
    void floorVisited(int floor);
    void floorSkipped(int floor);

private:
    void addFloorButton(int floor);

    Ui::Controller *ui;
    Controller* controller;

    std::vector<QRadioButton*> floorBulbs;
    std::vector<ControllerButton*> controllerButtons;
};

#endif // CONTROLLERWIDGET_H
