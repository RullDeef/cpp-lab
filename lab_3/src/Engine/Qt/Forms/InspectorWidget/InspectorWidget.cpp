#include <QPushButton>
#include "InspectorWidget.h"
#include "TransformWidget/TransformWidget.h"


InspectorWidget::InspectorWidget()
{
    ui.setupUi(this);
    setAllowedAreas(Qt::DockWidgetArea::AllDockWidgetAreas);
    setWindowTitle(u8"���������");
}

void InspectorWidget::inspect(IObject* object)
{
    while (auto w = widget()->findChild<QWidget*>())
        delete w;

    for (int i = 0; i < widget()->layout()->count(); ++i) {
        QLayoutItem* layoutItem = widget()->layout()->itemAt(i);
        widget()->layout()->removeItem(layoutItem);
        delete layoutItem;
        --i;
    }

    if (object)
    {
        this->object = object;

        QPushButton* deleteButton = new QPushButton();
        deleteButton->setText(u8"������� ����������");
        widget()->layout()->addWidget(deleteButton);
        connect(deleteButton, &QPushButton::pressed, this, &InspectorWidget::deleteButtonPressed);

        auto transformWidget = new TransformWidget(object->getTransform());
        widget()->layout()->addWidget(transformWidget);
        connect(transformWidget, &TransformWidget::transformChanged, this, &InspectorWidget::transformChangedSlot);

        auto spacer = new QSpacerItem(0, height() / 2, QSizePolicy::Fixed, QSizePolicy::Expanding);
        widget()->layout()->addItem(spacer);
    }
}

void InspectorWidget::transformChangedSlot()
{
    emit transformChanged();
}

void InspectorWidget::deleteButtonPressed()
{
    emit deleteObject(object);
}
