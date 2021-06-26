#include "HierarchyWidget.h"
#include "Qt/Forms/ObjectListItemWidget/ObjectListItemWidget.h"


HierarchyWidget::HierarchyWidget()
{
    ui.setupUi(this);
    setAllowedAreas(Qt::DockWidgetArea::AllDockWidgetAreas);
    setWindowTitle(u8"Иерархия объектов");
}

void HierarchyWidget::updateHierarchy(Scene& scene)
{
    clearWidgets();

    for (const auto& obj : scene)
        addListItem(obj);

    auto spacer = new QSpacerItem(0, height() / 2, QSizePolicy::Fixed, QSizePolicy::Expanding);
    widget()->layout()->addItem(spacer);
}

void HierarchyWidget::itemSelectionToggled(IObject* object, bool state)
{
    emit selectionToggled(object, state);
}

void HierarchyWidget::clearWidgets()
{
    while (auto w = widget()->findChild<QWidget*>())
        delete w;

    for (int i = 0; i < widget()->layout()->count(); ++i) {
        QLayoutItem* layoutItem = widget()->layout()->itemAt(i);
        widget()->layout()->removeItem(layoutItem);
        delete layoutItem;
        --i;
    }
}

void HierarchyWidget::addListItem(IObject* object)
{
    // if (object->isComposite())
    //     for (auto& inner : *object)
    //         addListItem(inner);
    // else
    {
        auto listItem = new ObjectListItemWidget(object);
        connect(listItem, &ObjectListItemWidget::selectionToggled, this, &HierarchyWidget::itemSelectionToggled);

        widget()->layout()->addWidget(listItem);
    }
}
