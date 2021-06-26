#include <stdexcept>
#include "SceneManager.hpp"


void SceneManager::setScene(std::shared_ptr<Scene> newScene)
{
    scene = newScene;
}

Scene& SceneManager::getScene()
{
    if (!scene)
        throw std::runtime_error("SceneManager::getScene: bad scene pointer");

    return *scene;
}

const Scene& SceneManager::getScene() const
{
    if (!scene)
        throw std::runtime_error("SceneManager::getScene: bad scene pointer");

    return *scene;
}
