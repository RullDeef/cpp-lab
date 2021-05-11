#pragma once

#include "Managers/SceneManager.hpp"

class Controller
{
public:
    Controller();

    void createEmptyScene();
    void loadScene(const char* filename);

    bool addSceneObject(std::shared_ptr<ISceneObject> object);

    void renderScene(std::shared_ptr<IRenderer> renderer);

private:
    SceneManager sceneManager;
};
