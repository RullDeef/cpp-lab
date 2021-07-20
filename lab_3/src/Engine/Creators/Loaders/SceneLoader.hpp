#pragma once

#include <string>

class Scene;


class SceneLoader
{
public:
    Scene* loadScene(const std::string& filename);
};
