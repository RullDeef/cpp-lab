#ifndef DOOR_H
#define DOOR_H

#include <QObject>


class Door : public QObject
{
    Q_OBJECT

public:
    enum class State
    {
        CLOSED,
        OPENING,
        OPENED,
        CLOSING
    };

    Door();
    virtual ~Door();

signals:
    void openedSignal(Door* door);
    void openingSignal(Door* door);
    void closingSignal(Door* door);
    void closedSignal(Door* door);

public slots:
    void openDoor();
    void closeDoor();

protected slots:
    void _finishOpening();
    void _finishClosing();

public:
    State state;
};

#endif // DOOR_H
