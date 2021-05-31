#pragma once

#include <memory>
#include "Scene.hpp"


class SceneBuilder
{
public:
    void startBuild();

    void addObject(std::shared_ptr<ISceneObject> object);

    std::shared_ptr<Scene> getResult();

private:
    std::shared_ptr<Scene> scene;
};
