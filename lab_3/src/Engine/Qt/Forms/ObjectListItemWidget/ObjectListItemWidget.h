#pragma once

#include <memory>
#include <QWidget>
#include "ui_ObjectListItemWidget.h"
#include "API/Objects/ISceneObject.hpp"


class ObjectListItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ObjectListItemWidget(std::shared_ptr<ISceneObject> object);
    virtual ~ObjectListItemWidget();

    void setObject(std::shared_ptr<ISceneObject> newObject);
    std::shared_ptr<ISceneObject> getObject();

signals:
    void selectionToggled(std::shared_ptr<ISceneObject> object, bool selected);

protected slots:
    void selectCheckboxToggled(bool state);

protected:
    void updateLabels();

private:
    Ui::ObjectListItemWidget ui;
    std::weak_ptr<ISceneObject> object;
};
