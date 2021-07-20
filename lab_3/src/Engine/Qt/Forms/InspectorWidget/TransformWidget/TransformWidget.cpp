#include <QPushButton>
#include "TransformWidget.h"


TransformWidget::TransformWidget(Transform& transform)
    : transform(transform)
{
    ui.setupUi(this);

    Vector position = transform.getPosition();
    Vector rotation = transform.getRotation();
    Vector scale = transform.getScale();

    pos = new NamedVectorWidget(QString(u8"Позиция"), position);
    rot = new NamedVectorWidget(QString(u8"Поворот"), rotation);
    scl = new NamedVectorWidget(QString(u8"Масштаб"), scale);

    ui.groupBox->layout()->addWidget(pos);
    ui.groupBox->layout()->addWidget(rot);
    ui.groupBox->layout()->addWidget(scl);

    auto applyButton = new QPushButton();
    applyButton->setText(u8"Применить");
    connect(applyButton, &QPushButton::pressed, this, &TransformWidget::applyButtonPressed);
    ui.groupBox->layout()->addWidget(applyButton);
}

void TransformWidget::applyButtonPressed()
{
    transform.setPosition(pos->getValue());
    transform.setRotation(rot->getValue());
    transform.setScale(scl->getValue());

    emit transformChanged();
}
