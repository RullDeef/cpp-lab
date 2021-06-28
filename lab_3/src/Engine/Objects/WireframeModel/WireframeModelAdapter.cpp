#include <stdexcept>
#include "Visitors/IObjectVisitor.hpp"
#include "WireframeModelAdapter.hpp"


WireframeModelAdapter::WireframeModelAdapter(const std::string& name, WireframeModel* model)
    : IObject(name), model(model)
{
}

WireframeModelAdapter::WireframeModelAdapter(WireframeModel* model)
    : model(model)
{
}

WireframeModelAdapter::~WireframeModelAdapter()
{
    if (model)
        delete model;
}

WireframeModel& WireframeModelAdapter::getModel()
{
    if (!model)
        throw std::runtime_error("WireframeModelAdapter: bad model pointer");
    return *model;
}

const WireframeModel& WireframeModelAdapter::getModel() const
{
    if (!model)
        throw std::runtime_error("WireframeModelAdapter: bad model pointer");
    return *model;
}

void WireframeModelAdapter::accept(IObjectVisitor& visitor)
{
    visitor.visit(*this);
}
