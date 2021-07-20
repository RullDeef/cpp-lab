#pragma once

#include <memory>

class Scene;


class SceneDirector
{
public:
    virtual std::shared_ptr<Scene> makeScene() = 0;
};
