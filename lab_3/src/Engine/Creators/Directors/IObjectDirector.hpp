#pragma once

class IObject;


class IObjectDirector
{
public:
    virtual ~IObjectDirector() = default;

    virtual IObject* makeObject() = 0;
};
