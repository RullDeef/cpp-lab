#ifndef CONTROLLERBUTTON_H
#define CONTROLLERBUTTON_H

#include <QObject>


class ControllerButton : public QObject
{
    Q_OBJECT

public:
    enum class State
    {
        PRESSED,
        RELEASED
    };

    explicit ControllerButton(int floor);
    virtual ~ControllerButton();

    int getFloorNumber() const;

signals:
    void pressedSignal(ControllerButton* button);
    void releasedSignal(ControllerButton* button);

public slots:
    void pressButton();
    void releaseButton();

private:
    int floorNumber;
    State state = State::RELEASED;
};

#endif // CONTROLLERBUTTON_H
