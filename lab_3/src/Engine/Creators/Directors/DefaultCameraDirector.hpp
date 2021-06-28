#pragma once

#include "IObjectDirector.hpp"


class DefaultCameraDirector : public IObjectDirector
{
public:
    IObject* makeObject() override;
};
