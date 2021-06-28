#include "TransformWidget.h"
#include "NamedVectorWidget/NamedVectorWidget.h"


TransformWidget::TransformWidget(const Transform& transform)
{
    ui.setupUi(this);

    Vector position = transform.getPosition();
    Vector rotation = transform.getRotation() * (180.0 / 3.1415);
    Vector scale = transform.getScale();
    
    ui.groupBox->layout()->addWidget(new NamedVectorWidget(QString(u8"Позиция"), position));
    ui.groupBox->layout()->addWidget(new NamedVectorWidget(QString(u8"Поворот"), rotation));
    ui.groupBox->layout()->addWidget(new NamedVectorWidget(QString(u8"Масштаб"), scale));
}
