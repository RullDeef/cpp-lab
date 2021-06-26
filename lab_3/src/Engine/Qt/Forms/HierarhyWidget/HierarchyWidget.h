#pragma once

#include <QDockWidget>
#include "ui_HierarchyWidget.h"
#include "Scene/Scene.hpp"
#include "Objects/IObject.hpp"


class HierarchyWidget : public QDockWidget
{
    Q_OBJECT

public:
    HierarchyWidget();
    virtual ~HierarchyWidget() = default;

    void updateHierarchy(Scene& scene);

signals:
    void selectionToggled(IObject* object, bool state);

protected slots:
    void itemSelectionToggled(IObject* object, bool state);

private:
    void clearWidgets();
    void addListItem(IObject* object);

    Ui::HierarchyWidget ui;
};
