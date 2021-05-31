#include "ISceneEvent.hpp"

ISceneEvent::ISceneEvent(std::shared_ptr<Scene> scene)
    : scene(scene)
{
}

const std::shared_ptr<Scene>& ISceneEvent::getScene() const
{
    return scene;
}
