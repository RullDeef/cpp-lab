#pragma once

#include "API/Objects/ISceneObject.hpp"
#include "HullModel.hpp"


class HullModelAdapter : public ISceneObject
{
public:
    HullModelAdapter(std::shared_ptr<HullModel> model);
    virtual ~HullModelAdapter() = default;

    virtual std::shared_ptr<ISceneObject> clone() const;

    virtual void accept(IObjectVisitor* visitor) override;
    virtual bool isVisible() const { return true; }

    virtual std::shared_ptr<Memento> saveState();
    virtual void restoreState(std::shared_ptr<Memento> memento);

    std::shared_ptr<HullModel> getModel();

    virtual ISceneObjectIterator begin();
    virtual ISceneObjectIterator end();
    virtual ISceneObjectConstIterator begin() const;
    virtual ISceneObjectConstIterator end() const;

private:
    std::shared_ptr<HullModel> model;
};
