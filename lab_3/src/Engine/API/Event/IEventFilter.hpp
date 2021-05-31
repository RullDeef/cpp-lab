#pragma once

#include <memory>
#include <list>
#include "IEvent.hpp"


class IEventFilter
{
public:
    virtual ~IEventFilter();

    void addFilter(std::shared_ptr<IEventFilter> filter);
    virtual bool accept(IEvent* event);

private:
    std::list<std::shared_ptr<IEventFilter>> filters;
};
