#pragma once

#include <memory>
#include "API/Objects/ISceneObject.hpp"


class Scene
{
public:
    Scene() = default;
    template<typename InputIt>
    Scene(InputIt iterStart, InputIt iterEnd) : objects(iterStart, iterEnd) {}

    std::list<std::shared_ptr<ISceneObject>>::iterator begin();
    std::list<std::shared_ptr<ISceneObject>>::iterator end();

    std::list<std::shared_ptr<ISceneObject>>::const_iterator begin() const;
    std::list<std::shared_ptr<ISceneObject>>::const_iterator end() const;

private:
    std::list<std::shared_ptr<ISceneObject>> objects;
};
