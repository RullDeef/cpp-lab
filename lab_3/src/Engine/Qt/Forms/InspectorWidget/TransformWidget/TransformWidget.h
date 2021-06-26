#pragma once

#include <QWidget>
//#include "Core/Math/Transform.hpp"
#include "ui_TransformWidget.h"


class TransformWidget : public QWidget
{
    Q_OBJECT

public:
    //explicit TransformWidget(const Transform& transform);
    virtual ~TransformWidget() = default;

private:
    Ui::TransformWidget ui;
};
