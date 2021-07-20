#pragma once

#include <QWidget>
#include "Objects/Transform/Transform.hpp"
#include "NamedVectorWidget/NamedVectorWidget.h"
#include "ui_TransformWidget.h"


class TransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransformWidget(Transform& transform);
    virtual ~TransformWidget() = default;

signals:
    void transformChanged();

protected slots:
    void applyButtonPressed();

private:
    Ui::TransformWidget ui;

    Transform& transform;

    NamedVectorWidget* pos;
    NamedVectorWidget* rot;
    NamedVectorWidget* scl;
};
