#include "IEventFilter.hpp"

IEventFilter::~IEventFilter()
{
}

void IEventFilter::addFilter(std::shared_ptr<IEventFilter> filter)
{
    filters.push_back(filter);
}

bool IEventFilter::accept(IEvent* event)
{
    for (auto& filter : filters)
        if (!filter->accept(event))
            return false;
    return true;
}
