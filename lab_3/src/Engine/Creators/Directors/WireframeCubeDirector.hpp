#pragma once

#include "IObjectDirector.hpp"


class WireframeCubeDirector : public IObjectDirector
{
public:
    std::shared_ptr<IObject> makeObject() override;
};
