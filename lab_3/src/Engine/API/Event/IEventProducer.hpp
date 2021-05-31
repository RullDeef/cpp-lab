#pragma once

#include "IEvent.hpp"


class IEventProducer
{
public:
    virtual void postEvent(IEvent* event) = 0;
};
