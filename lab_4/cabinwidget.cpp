#include "cabinwidget.h"
#include "ui_cabinwidget.h"


CabinWidget::CabinWidget(Cabin* cabin, Door* door)
    : ui(new Ui::Elevator), cabin(cabin), door(door)
{
    ui->setupUi(this);

    connect(door, &Door::openingSignal, this, &CabinWidget::playDoorsOpenAnimation);
    connect(door, &Door::closingSignal, this, &CabinWidget::playDoorsCloseAnimation);

    playDoorsOpenAnimation();
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
    }

    ui->spacer->changeSize(w, h);
    layout()->invalidate();

    timer.setInterval(10);
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
    }

    ui->spacer->changeSize(w, h);
    layout()->invalidate();

    timer.setInterval(10);
}

void CabinWidget::playDoorsOpenAnimation()
{
    connect(&timer, &QTimer::timeout, this, &CabinWidget::doorOpenTick);
    timer.start(500);
}

void CabinWidget::playDoorsCloseAnimation()
{
    connect(&timer, &QTimer::timeout, this, &CabinWidget::doorCloseTick);
    timer.start(500);
}
