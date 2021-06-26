#include <stdexcept>
#include "HullModelAdapter.hpp"
#include "API/Objects/IObjectVisitor.hpp"


HullModelAdapter::HullModelAdapter(std::shared_ptr<HullModel> model)
    : model(model)
{
}

std::shared_ptr<ISceneObject> HullModelAdapter::clone() const
{
    throw std::runtime_error("not implemented exception");
}

void HullModelAdapter::accept(IObjectVisitor* visitor)
{
    visitor->visit(*this);
}

std::shared_ptr<Memento> HullModelAdapter::saveState()
{
    throw std::runtime_error("not implemented exception");
}

void HullModelAdapter::restoreState(std::shared_ptr<Memento> memento)
{
    throw std::runtime_error("not implemented exception");
}

std::shared_ptr<HullModel> HullModelAdapter::getModel()
{
    return model;
}

ISceneObject::ISceneObjectIterator HullModelAdapter::begin()
{
    throw std::runtime_error("not implemented exception");
}

ISceneObject::ISceneObjectIterator HullModelAdapter::end()
{
    throw std::runtime_error("not implemented exception");
}

ISceneObject::ISceneObjectConstIterator HullModelAdapter::begin() const
{
    throw std::runtime_error("not implemented exception");
}

ISceneObject::ISceneObjectConstIterator HullModelAdapter::end() const
{
    throw std::runtime_error("not implemented exception");
}
