#pragma once

#include <memory>
#include "IObjectDirector.hpp"


class DefaultCameraDirector : public IObjectDirector
{
public:
    std::shared_ptr<IObject> makeObject() override;
};
