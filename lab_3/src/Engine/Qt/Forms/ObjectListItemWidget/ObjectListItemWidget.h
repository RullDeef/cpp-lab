#pragma once

#include <QWidget>
#include "ui_ObjectListItemWidget.h"
#include "Objects/IObject.hpp"


class ObjectListItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ObjectListItemWidget(IObject* object);
    virtual ~ObjectListItemWidget() = default;

    void setObject(IObject* newObject);
    IObject* getObject();

signals:
    void selectionToggled(IObject* object, bool selected);

protected slots:
    void selectCheckboxToggled(bool state);

protected:
    void updateLabels();

private:
    Ui::ObjectListItemWidget ui;
    IObject* object;
};
