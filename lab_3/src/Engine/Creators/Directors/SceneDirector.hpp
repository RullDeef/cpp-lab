#pragma once

class Scene;


class SceneDirector
{
public:
    virtual Scene* makeScene() = 0;
};
