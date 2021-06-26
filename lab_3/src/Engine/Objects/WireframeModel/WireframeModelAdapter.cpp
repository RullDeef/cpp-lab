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

void WireframeModelAdapter::accept(IObjectVisitor& visitor)
{
    visitor.visit(*this);
}
