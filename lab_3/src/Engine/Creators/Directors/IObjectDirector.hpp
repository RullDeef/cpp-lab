#pragma once

#include <memory>

class IObject;


class IObjectDirector
{
public:
    virtual ~IObjectDirector() = default;

    virtual std::shared_ptr<IObject> makeObject() = 0;
};
