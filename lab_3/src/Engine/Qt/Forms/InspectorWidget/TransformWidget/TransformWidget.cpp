#include "TransformWidget.h"
#include "NamedVectorWidget/NamedVectorWidget.h"


TransformWidget::TransformWidget(const Transform& transform)
{
    ui.setupUi(this);

    Vector position = transform.getPosition();
    Vector rotation = transform.getRotation() * (180.0 / 3.1415);
    Vector scale = transform.getScale();
    
    ui.groupBox->layout()->addWidget(new NamedVectorWidget(QString(u8"�������"), position));
    ui.groupBox->layout()->addWidget(new NamedVectorWidget(QString(u8"�������"), rotation));
    ui.groupBox->layout()->addWidget(new NamedVectorWidget(QString(u8"�������"), scale));
}
