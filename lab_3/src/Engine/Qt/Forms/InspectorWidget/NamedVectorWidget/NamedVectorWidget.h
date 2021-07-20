#pragma once

#include <QWidget>
#include "Core/Math/Vector.hpp"
#include "ui_NamedVectorWidget.h"


class NamedVectorWidget : public QWidget
{
    Q_OBJECT

public:
    NamedVectorWidget(const QString& name, const Vector& vector);
    virtual ~NamedVectorWidget() = default;

    Vector getValue() const;

private:
    Ui::NamedVectorWidget ui;
};
