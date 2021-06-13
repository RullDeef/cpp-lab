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
    else
        qDebug() << "Doors: ignored transition from "
            << (state == State::OPENED ? "OPENED" : "OPENING")
            << " to OPENING";
}

void Door::closing()
{
    if (state == State::OPENED)
    {
        qDebug() << "door is closing...";
        state = State::CLOSING;
        emit closingSignal(this);
    }
    else
        qDebug() << "Doors: ignored transition from "
            << (state == State::OPENING ? "OPENING" :
               (state == State::CLOSING ? "CLOSING" : "CLOSED"))
            << " to CLOSING";
}

void Door::open()
{
    if (state == State::OPENING)
    {
        qDebug() << "door opened.";
        state = State::OPENED;
        emit openedSignal(this);
    }
    else
        qDebug() << "Doors: ignored transition from "
            << (state == State::OPENED ? "OPENED" :
               (state == State::CLOSING ? "CLOSING" : "CLOSED"))
            << " to OPENED";
}

void Door::close()
{
    if (state == State::CLOSING)
    {
        qDebug() << "door closed.";
        state = State::CLOSED;
        emit closedSignal(this);
    }
    else
        qDebug() << "Doors: ignored transition from "
            << (state == State::OPENED ? "OPENED" :
               (state == State::CLOSED ? "CLOSED" : "OPENING"))
            << " to CLOSED";
}
