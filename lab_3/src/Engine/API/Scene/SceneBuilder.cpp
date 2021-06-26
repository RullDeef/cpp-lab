#include "SceneBuilder.hpp"

void SceneBuilder::startBuild()
{
    scene = std::make_shared<Scene>();
}

void SceneBuilder::addObject(std::shared_ptr<ISceneObject> object)
{
    scene->addChild(object);
}

std::shared_ptr<Scene> SceneBuilder::getResult()
{
    return std::move(scene);
}
