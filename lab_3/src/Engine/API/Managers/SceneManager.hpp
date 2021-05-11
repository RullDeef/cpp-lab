#pragma once

#include "Scene/Scene.hpp"
#include "Scene/ICamera.hpp"
#include "Renderer/IRenderer.hpp"

class SceneManager
{
public:
    SceneManager();

    void createEmptyScene();
    void loadScene(const char* filename);

    bool addSceneObject(std::shared_ptr<ISceneObject> object);

    void renderScene(std::shared_ptr<IRenderer> renderer, std::shared_ptr<ICamera> camera);

private:
    std::shared_ptr<Scene> scene;
};
