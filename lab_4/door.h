#ifndef DOOR_H
#define DOOR_H

#include <QObject>

class Door : public QObject
{
    Q_OBJECT

public:
    explicit Door(QObject *parent = nullptr);

signals:
    void opened();
    void closed();

public slots:
    void open();
    void close();

private:
    int timeout = 1000;
};

#endif // DOOR_H
