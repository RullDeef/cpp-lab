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

    void addObject(std::shared_ptr<ISceneObject> object);

    virtual void applyTransform(const Transform& t) override;
    virtual std::shared_ptr<ISceneObject> clone() const override;

    virtual void accept(std::shared_ptr<IObjectVisitor> visitor) override;

    virtual void addChild(std::shared_ptr<ISceneObject> object) override;
    virtual void removeChild(std::shared_ptr<ISceneObject> object) override;

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
