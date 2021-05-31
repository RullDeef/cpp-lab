#pragma once

#include "ISceneEvent.hpp"


class SceneChangedEvent : public ISceneEvent
{
public:
    SceneChangedEvent(std::shared_ptr<Scene> scene);
};
