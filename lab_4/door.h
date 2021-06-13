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
        CLOSING,
        OPENED,
        OPENING
    };

    Door() = default;
    virtual ~Door() = default;

signals:
    void openedSignal(Door* door);
    void openingSignal(Door* door);
    void closingSignal(Door* door);
    void closedSignal(Door* door);

public slots:
    void opening();
    void closing();
    void open();
    void close();

public:
    State state = State::CLOSED;
};

#endif // DOOR_H
