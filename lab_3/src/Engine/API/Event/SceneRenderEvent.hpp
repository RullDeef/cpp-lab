#pragma once

#include "ISceneEvent.hpp"


class SceneRenderEvent : public ISceneEvent
{
public:
    SceneRenderEvent(std::shared_ptr<Scene> scene);
};
