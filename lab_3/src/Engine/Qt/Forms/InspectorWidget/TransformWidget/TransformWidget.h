#pragma once

#include <QWidget>
#include "Objects/Transform/Transform.hpp"
#include "ui_TransformWidget.h"


class TransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransformWidget(const Transform& transform);
    virtual ~TransformWidget() = default;

private:
    Ui::TransformWidget ui;
};
