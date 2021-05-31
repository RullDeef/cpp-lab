#ifndef CABINWIDGET_H
#define CABINWIDGET_H

#include <QWidget>
#include <QTimer>

#include "cabin.h"

namespace Ui {
class Elevator;
}

class CabinWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CabinWidget(Cabin* cabin);
    ~CabinWidget();

    Cabin* operator->();
    Cabin& operator*();

public slots:
    void onDoorsOpened();
    void onDoorsClosed();

    void doorOpenTick();
    void doorCloseTick();

private:
    void playDoorsOpenAnimation();
    void playDoorsCloseAnimation();

    Ui::Elevator *ui;
    Cabin* cabin;
    QTimer timer;
};

#endif // CABINWIDGET_H
