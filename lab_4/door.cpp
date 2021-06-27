#include <QDebug>
#include "door.h"


void Door::opening()
{
    if (state == State::CLOSED || state == State::CLOSING)
    {
        qDebug() << "door is opening...";
        state = State::OPENING;
        emit openingSignal(this);
    }
}

void Door::closing()
{
    if (state == State::OPENED)
    {
        qDebug() << "door is closing...";
        state = State::CLOSING;
        emit closingSignal(this);
    }
}

void Door::open()
{
    if (state == State::OPENING)
    {
        qDebug() << "door opened.";
        state = State::OPENED;
        emit openedSignal(this);
    }
}

void Door::close()
{
    if (state == State::CLOSING)
    {
        qDebug() << "door closed.";
        state = State::CLOSED;
        emit closedSignal(this);
    }
}
