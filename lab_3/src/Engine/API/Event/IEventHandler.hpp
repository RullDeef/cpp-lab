#pragma once

#include "IEvent.hpp"
#include "IEventProducer.hpp"


template<class EventType>
class IEventHandler
{
public:
    virtual void handle(EventType* event, IEventProducer* producer) = 0;
};

template<class EventType, class... Other>
class IEventsHandler : public IEventHandler<EventType>, public IEventsHandler<Other...>
{};

template<class EventType>
class IEventsHandler : public IEventHandler<EventType>
{};
