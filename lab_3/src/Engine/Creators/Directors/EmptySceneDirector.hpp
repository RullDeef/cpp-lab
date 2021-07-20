#pragma once

#include "SceneDirector.hpp"


class EmptySceneDirector : public SceneDirector
{
public:
    virtual std::shared_ptr<Scene> makeScene() override;
};
