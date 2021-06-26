#include "NamedVectorWidget.h"


NamedVectorWidget::NamedVectorWidget(const QString& name, const Vector& vector)
{
    ui.setupUi(this);

    ui.groupBox->setTitle(name);
    ui.xInput->setValue(vector.getX());
    ui.yInput->setValue(vector.getY());
    ui.zInput->setValue(vector.getZ());
}
