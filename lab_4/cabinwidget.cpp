#include "cabinwidget.h"
#include "ui_cabinwidget.h"

CabinWidget::CabinWidget(Cabin* cabin)
    : QWidget(nullptr), ui(new Ui::Elevator), cabin(cabin)
{
    ui->setupUi(this);

    connect(cabin, &Cabin::doorsOpening, this, &CabinWidget::playDoorsOpenAnimation);
    connect(cabin, &Cabin::doorsClosing, this, &CabinWidget::playDoorsCloseAnimation);

    playDoorsOpenAnimation();
}

CabinWidget::~CabinWidget()
{
    delete ui;
}

Cabin *CabinWidget::operator->()
{
    return cabin;
}

Cabin &CabinWidget::operator*()
{
    return *cabin;
}

void CabinWidget::onDoorsOpened()
{

}

void CabinWidget::onDoorsClosed()
{

}

void CabinWidget::doorOpenTick()
{
    int w = ui->spacer->sizeHint().width();
    int h = ui->spacer->sizeHint().height();

    w += 1;

    if (w >= width() - 50)
    {
        w = width() - 50;
        timer.stop();
        timer.disconnect();
        // emit doorsClosed();
    }

    ui->spacer->changeSize(w, h);
    layout()->invalidate();
}

void CabinWidget::doorCloseTick()
{
    int w = ui->spacer->sizeHint().width();
    int h = ui->spacer->sizeHint().height();

    w -= 1;

    if (w <= 0)
    {
        w = 0;
        timer.stop();
        timer.disconnect();
        // emit doorsClosed();
    }

    ui->spacer->changeSize(w, h);
    layout()->invalidate();
}

void CabinWidget::playDoorsOpenAnimation()
{
    connect(&timer, &QTimer::timeout, this, &CabinWidget::doorOpenTick);
    timer.start(1);
}

void CabinWidget::playDoorsCloseAnimation()
{
    connect(&timer, &QTimer::timeout, this, &CabinWidget::doorCloseTick);
    timer.start(1);
}
