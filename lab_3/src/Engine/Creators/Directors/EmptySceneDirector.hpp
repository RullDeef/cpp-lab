#pragma once

#include "SceneDirector.hpp"


class EmptySceneDirector : public SceneDirector
{
public:
    virtual Scene* makeScene() override;
};
