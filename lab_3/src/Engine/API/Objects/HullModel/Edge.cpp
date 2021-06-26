#include "Edge.hpp"
#include "API/Objects/IObjectVisitor.hpp"


void Edge::accept(IObjectVisitor* visitor)
{
    visitor->visit(*this);
}
