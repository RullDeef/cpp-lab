#include <QTimer>
#include <QDebug>
#include "door.h"

Door::Door(QObject *parent) : QObject(parent)
{
}

void Door::open()
{
    qDebug() << "door is opening...";
    QTimer::singleShot(timeout, this, &Door::opened);
}

void Door::close()
{
    qDebug() << "door is closing...";
    QTimer::singleShot(timeout, this, &Door::closed);
}
