#pragma once

#include <QDockWidget>
#include "ui_HierarchyWidget.h"
#include "API/Scene/Scene.hpp"


class HierarchyWidget : public QDockWidget
{
    Q_OBJECT

public:
    HierarchyWidget();
    virtual ~HierarchyWidget() = default;

    void updateHierarchy(const Scene& scene);

signals:
    void selectionToggled(std::shared_ptr<ISceneObject> object, bool state);

protected slots:
    void itemSelectionToggled(std::shared_ptr<ISceneObject> object, bool state);

private:
    void clearWidgets();
    void addListItem(std::shared_ptr<ISceneObject> object);

    Ui::HierarchyWidget ui;
};
