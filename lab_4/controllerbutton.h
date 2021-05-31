#ifndef CONTROLLERBUTTON_H
#define CONTROLLERBUTTON_H

#include <QPushButton>

class ControllerButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ControllerButton(QWidget *parent = nullptr);
    ~ControllerButton();

    void setNumber(int n);

public slots:
    void makeRequest();

signals:
    void requestFloor(int n);

private:
    int floorNumber = 0;
};

#endif // CONTROLLERBUTTON_H
