#pragma once

#include "IObjectDirector.hpp"


class WireframeCubeDirector : public IObjectDirector
{
public:
    IObject* makeObject() override;
};
