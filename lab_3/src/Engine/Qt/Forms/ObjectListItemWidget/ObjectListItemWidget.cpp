#include "ObjectListItemWidget.h"

ObjectListItemWidget::ObjectListItemWidget(IObject* object)
    : object(object)
{
    ui.setupUi(this);
    updateLabels();

    connect(ui.selectedCheckBox, &QCheckBox::toggled, this, &ObjectListItemWidget::selectCheckboxToggled);
}

void ObjectListItemWidget::setObject(IObject* newObject)
{
    object = newObject;
    updateLabels();
}

IObject* ObjectListItemWidget::getObject()
{
    return object;
}

void ObjectListItemWidget::selectCheckboxToggled(bool state)
{
    emit selectionToggled(object, state);
}

void ObjectListItemWidget::updateLabels()
{
    ui.objectNameLabel->setText(QString::fromStdString(object->getName()));
    // ui.visibleCheckBox->setChecked(object->isVisible());
}
