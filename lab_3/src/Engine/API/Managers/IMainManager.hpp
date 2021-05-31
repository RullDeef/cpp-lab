#pragma once

#include "IManager.hpp"


class IMainManager
{
public:
    virtual ~IMainManager() = default;

    virtual void shutDown() = 0;
};
