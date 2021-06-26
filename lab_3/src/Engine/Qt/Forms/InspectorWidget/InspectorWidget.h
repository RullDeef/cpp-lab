#pragma once

#include <QDockWidget>
#include "Objects/IObject.hpp"
#include "ui_InspectorWidget.h"


class InspectorWidget : public QDockWidget
{
    Q_OBJECT

public:
    InspectorWidget();
    virtual ~InspectorWidget() = default;

    void inspect(IObject* object);

private:
    Ui::InspectorWidget ui;

    IObject* object;
};
