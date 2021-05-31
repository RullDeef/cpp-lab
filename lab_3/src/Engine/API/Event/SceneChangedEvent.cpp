#include "SceneChangedEvent.hpp"

SceneChangedEvent::SceneChangedEvent(std::shared_ptr<Scene> scene)
    : ISceneEvent(scene)
{
}
