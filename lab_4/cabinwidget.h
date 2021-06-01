#ifndef CABINWIDGET_H
#define CABINWIDGET_H

#include <QWidget>
#include <QTimer>
#include "cabin.h"
#include "door.h"


namespace Ui {
class Elevator;
}

class CabinWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CabinWidget(Cabin* cabin, Door* door);
    virtual ~CabinWidget();

public slots:
    void doorOpenTick();
    void doorCloseTick();

private:
    void playDoorsOpenAnimation();
    void playDoorsCloseAnimation();

    Ui::Elevator *ui;
    Cabin* cabin;
    Door* door;
    QTimer timer;
};

#endif // CABINWIDGET_H
