#include <QTimer>
#include <QDebug>
#include "door.h"

constexpr int timeout = 3000;

Door::Door() : QObject(nullptr)
{
}

Door::~Door()
{
    qDebug() << "door removed!";
}

void Door::openDoor()
{
    qDebug() << "door is opening...";
    state = State::OPENING;
    emit openingSignal(this);
    QTimer::singleShot(timeout, this, &Door::_finishOpening);
}

void Door::closeDoor()
{
    qDebug() << "door is closing...";
    state = State::CLOSING;
    emit closingSignal(this);
    QTimer::singleShot(timeout, this, &Door::_finishClosing);
}

void Door::_finishOpening()
{
    state = State::OPENED;
    emit openedSignal(this);
}

void Door::_finishClosing()
{
    state = State::CLOSED;
    emit closedSignal(this);
}
