#pragma once

#include "IEvent.hpp"
#include "../Scene/Scene.hpp"


class ISceneEvent : public IEvent
{
public:
    ISceneEvent(std::shared_ptr<Scene> scene);

    const std::shared_ptr<Scene>& getScene() const;

private:
    std::shared_ptr<Scene> scene;
};
