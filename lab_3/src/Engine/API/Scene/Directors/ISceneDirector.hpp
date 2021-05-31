#pragma once

#include <memory>
#include "API/Scene/Scene.hpp"


class ISceneDirector
{
public:
    virtual ~ISceneDirector() = default;

    virtual std::shared_ptr<Scene> makeScene() = 0;
};
