#include "ObjectListItemWidget.h"

ObjectListItemWidget::ObjectListItemWidget(std::shared_ptr<ISceneObject> object)
    : object(object)
{
    ui.setupUi(this);
    updateLabels();

    connect(ui.selectedCheckBox, &QCheckBox::toggled, this, &ObjectListItemWidget::selectCheckboxToggled);
}

ObjectListItemWidget::~ObjectListItemWidget()
{
}

void ObjectListItemWidget::setObject(std::shared_ptr<ISceneObject> newObject)
{
    object = newObject;
    updateLabels();
}

std::shared_ptr<ISceneObject> ObjectListItemWidget::getObject()
{
    return object.lock();
}

void ObjectListItemWidget::selectCheckboxToggled(bool state)
{
    if (auto ptr = object.lock())
        emit selectionToggled(ptr, state);
}

void ObjectListItemWidget::updateLabels()
{
    if (auto ptr = object.lock())
    {
        ui.objectNameLabel->setText(QString::fromStdString(ptr->getName()));
        ui.visibleCheckBox->setChecked(ptr->isVisible());
    }
    else
    {
        ui.objectNameLabel->setText("?");
        ui.visibleCheckBox->setChecked(false);
    }
}
