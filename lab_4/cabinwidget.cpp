#include "cabinwidget.h"
#include "ui_cabinwidget.h"


CabinWidget::CabinWidget(Cabin* cabin, Door* door)
    : ui(new Ui::Elevator), cabin(cabin), door(door)
{
    ui->setupUi(this);

    connect(door, &Door::openingSignal, this, &CabinWidget::playDoorsOpenAnimation);
    connect(door, &Door::closingSignal, this, &CabinWidget::playDoorsCloseAnimation);
}

CabinWidget::~CabinWidget()
{
    delete ui;
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
        door->open();
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
        door->close();
    }

    ui->spacer->changeSize(w, h);
    layout()->invalidate();
}

void CabinWidget::playDoorsOpenAnimation()
{
    timer.stop();
    timer.disconnect();
    connect(&timer, &QTimer::timeout, this, &CabinWidget::doorOpenTick);
    timer.start(10);
}

void CabinWidget::playDoorsCloseAnimation()
{
    timer.stop();
    timer.disconnect();
    connect(&timer, &QTimer::timeout, this, &CabinWidget::doorCloseTick);
    timer.start(10);
}
