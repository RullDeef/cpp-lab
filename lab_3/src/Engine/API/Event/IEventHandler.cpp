#include "IEventHandler.hpp"

const std::shared_ptr<IEventFilter>& IEventHandler::getFilter() const
{
    return filter;
}

void IEventHandler::setFilter(std::shared_ptr<IEventFilter> newFilter)
{
    filter = newFilter;
}
