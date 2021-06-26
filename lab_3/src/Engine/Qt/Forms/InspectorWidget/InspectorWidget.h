#pragma once

#include <QDockWidget>
#include "API/Objects/ISceneObject.hpp"
#include "ui_InspectorWidget.h"


class InspectorWidget : public QDockWidget
{
    Q_OBJECT

public:
    InspectorWidget();
    virtual ~InspectorWidget() = default;

    void inspect(std::shared_ptr<ISceneObject> object);

private:
    Ui::InspectorWidget ui;

    std::weak_ptr<ISceneObject> object;
};
