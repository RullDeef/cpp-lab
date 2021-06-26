#pragma once

#include <list>
#include <memory>
#include <iterator>
#include "ISceneObject.hpp"

class IRenderer;


class SceneObjectGroup : public ISceneObject
{
public:
    SceneObjectGroup(const std::string& name = "");

    virtual std::shared_ptr<ISceneObject> clone() const override;

    virtual void accept(IObjectVisitor* visitor) override;

    virtual void addChild(std::shared_ptr<ISceneObject> object) override;
    virtual void removeChild(std::shared_ptr<ISceneObject> object) override;

    bool hasChild(std::shared_ptr<ISceneObject> object) const;
    size_t size() const;

    virtual bool isComposite() const override { return true; }
    virtual bool isVisible() const override;

    virtual std::shared_ptr<Memento> saveState() override { return nullptr; }
    virtual void restoreState(std::shared_ptr<Memento> memento) override {}

    virtual std::list<std::shared_ptr<ISceneObject>>::iterator begin() override;
    virtual std::list<std::shared_ptr<ISceneObject>>::iterator end() override;

    virtual std::list<std::shared_ptr<ISceneObject>>::const_iterator begin() const override;
    virtual std::list<std::shared_ptr<ISceneObject>>::const_iterator end() const override;

private:
    std::list<std::shared_ptr<ISceneObject>> objects;
};
