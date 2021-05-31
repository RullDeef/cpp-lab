#include "SceneRenderEvent.hpp"

SceneRenderEvent::SceneRenderEvent(std::shared_ptr<Scene> scene)
    : ISceneEvent(scene)
{
}
