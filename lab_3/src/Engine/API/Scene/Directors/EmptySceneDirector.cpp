#include "EmptySceneDirector.hpp"

EmptySceneDirector::EmptySceneDirector(std::shared_ptr<SceneBuilder> builder)
    : builder(builder)
{
}

std::shared_ptr<Scene> EmptySceneDirector::makeScene()
{
    builder->startBuild();
    return builder->getResult();
}
