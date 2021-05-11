#pragma once

#include <list>
#include <memory>
#include <iterator>
#include "ISceneObject.hpp"

class SceneObjectGroup : public ISceneObject
{
public:
    void addObject(std::shared_ptr<ISceneObject> object);

    virtual void draw(std::shared_ptr<IRenderer> renderer) const override;

    std::list<std::shared_ptr<ISceneObject>>::iterator begin();
    std::list<std::shared_ptr<ISceneObject>>::iterator end();

    std::list<std::shared_ptr<ISceneObject>>::const_iterator begin() const;
    std::list<std::shared_ptr<ISceneObject>>::const_iterator end() const;

private:
    std::list<std::shared_ptr<ISceneObject>> objects;
};
